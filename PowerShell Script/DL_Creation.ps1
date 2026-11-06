

[CmdletBinding(SupportsShouldProcess = $true, ConfirmImpact = 'High')]
param(
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]$DGName,

    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]$DGAlias,

    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]$DGEmail,

    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]$CsvPath
)

$ErrorActionPreference = 'Stop'
$connected = $false
$added = 0
$skipped = 0
$failed = 0

try {
    if (-not (Test-Path -LiteralPath $CsvPath -PathType Leaf)) {
        throw "CSV file not found: $CsvPath"
    }

    $rows = @(Import-Csv -LiteralPath $CsvPath -ErrorAction Stop)

    if ($rows.Count -eq 0) {
        throw "The CSV has no data rows."
    }

    if ($rows[0].PSObject.Properties.Name -notcontains 'EmailAddress') {
        throw "The CSV must contain an 'EmailAddress' column."
    }

    # Remove blank addresses and duplicate rows before making changes.
    $seen = [System.Collections.Generic.HashSet[string]]::new(
        [System.StringComparer]::OrdinalIgnoreCase
    )
    $members = @(
        foreach ($row in $rows) {
            $address = ([string]$row.EmailAddress).Trim()

            if (-not [string]::IsNullOrWhiteSpace($address) -and $seen.Add($address)) {
                $address
            }
        }
    )

    if ($members.Count -eq 0) {
        throw "The CSV contains no usable EmailAddress values."
    }

    # Preview the intended work without connecting to Exchange Online.
    if ($WhatIfPreference) {
        $null = $PSCmdlet.ShouldProcess($DGEmail, "Create distribution group '$DGName'")
        foreach ($address in $members) {
            $null = $PSCmdlet.ShouldProcess($address, "Add to distribution group '$DGName'")
        }
        return
    }

    Connect-ExchangeOnline -ShowBanner:$false -ErrorAction Stop
    $connected = $true

    # Refuse to reuse an existing group. This avoids changing a group
    # unintentionally if the script is run with the wrong inputs.
    $existingGroup = $null
    try {
        $existingGroup = Get-DistributionGroup -Identity $DGEmail -ErrorAction Stop
    }
    catch {
        if ($_.CategoryInfo.Category -ne
            [System.Management.Automation.ErrorCategory]::ObjectNotFound) {
            throw
        }
    }

    if ($null -ne $existingGroup) {
        throw "A distribution group already exists for '$DGEmail'. No members were changed."
    }

    if (-not $PSCmdlet.ShouldProcess($DGEmail, "Create distribution group '$DGName'")) {
        return
    }

    New-DistributionGroup `
        -Name $DGName `
        -Alias $DGAlias `
        -PrimarySmtpAddress $DGEmail `
        -Confirm:$false `
        -ErrorAction Stop | Out-Null

    $currentMembers = @(
        Get-DistributionGroupMember `
            -Identity $DGEmail `
            -ResultSize Unlimited `
            -ErrorAction Stop
    )

    $currentAddresses = [System.Collections.Generic.HashSet[string]]::new(
        [System.StringComparer]::OrdinalIgnoreCase
    )
    foreach ($currentMember in $currentMembers) {
        $currentAddress = [string]$currentMember.PrimarySmtpAddress
        if (-not [string]::IsNullOrWhiteSpace($currentAddress)) {
            $null = $currentAddresses.Add($currentAddress)
        }
    }

    foreach ($address in $members) {
        if ($currentAddresses.Contains($address)) {
            Write-Host "Skipped (already a member): $address"
            $skipped++
            continue
        }

        if (-not $PSCmdlet.ShouldProcess($address, "Add to distribution group '$DGName'")) {
            $skipped++
            continue
        }

        try {
            Add-DistributionGroupMember `
                -Identity $DGEmail `
                -Member $address `
                -Confirm:$false `
                -ErrorAction Stop

            Write-Host "Added: $address"
            $added++
            $null = $currentAddresses.Add($address)
        }
        catch {
            Write-Warning "Failed to add '$address': $($_.Exception.Message)"
            $failed++
        }
    }

    Write-Host ''
    Write-Host "Summary for '$DGName' ($DGEmail)"
    Write-Host "  Added:   $added"
    Write-Host "  Skipped: $skipped"
    Write-Host "  Failed:  $failed"

    if ($failed -gt 0) {
        throw "$failed member(s) could not be added."
    }
}
catch {
    Write-Error $_
    throw
}
finally {
    if ($connected) {
        Disconnect-ExchangeOnline -Confirm:$false -ErrorAction SilentlyContinue |
            Out-Null
    }
}