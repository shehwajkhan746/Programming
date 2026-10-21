

Get-RetentionCompliancePolicy -Identity "b0f9c489-9bfd-4d99-8387-b00379463a29" -DistributionDetail | 

    Format-List Name, Guid, Enabled, Mode, Workload, *Location*


Get-AppRetentionCompliancePolicy

Set-RetentionCompliancePolicy `
7
    -Identity "b0f9c489-9bfd-4d99-8387-b00379463a29" `
8
    -Enabled $false


# Prereqs

Install-Module -Name PnP.PowerShell -Scope CurrentUser


# Connect (site collection admin)

$SiteURL = "https://<tenant>.sharepoint.com/sites/<site>"

Connect-PnPOnline -Url $SiteURL -Interactive


# ---- Delete ALL items from the PHL (sends them to first-stage recycle bin) ----

$ListName = "Preservation Hold Library"

Get-PnPListItem -List $ListName -PageSize 500 | ForEach-Object {

    Write-Host "Deleting: $($_.FieldValues.FileLeafRef)" -ForegroundColor Cyan

    Remove-PnPListItem -List $ListName -Identity $_.Id -Force -Recycle

}


# ---- Empty both recycle bins to actually reclaim quota ----

Clear-PnPRecycleBinItem -Force            # first stage

Clear-PnPRecycleBinItem -SecondStage -Force   # second stage (permanent)