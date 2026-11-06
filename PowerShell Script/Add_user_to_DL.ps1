

# Connect to Exchange Online
Connect-ExchangeOnline

# Create Distribution List
$DGName = "IT Support Team"
$DGAlias = "ITSupportTeam"
$DGEmail = "ITSupportTeam@contoso.com"

New-DistributionGroup `
-Name $DGName `
-Alias $DGAlias `
-PrimarySmtpAddress $DGEmail

# Import users and add to DL
Import-Csv "C:\Temp\Users.csv" | ForEach-Object {
    Add-DistributionGroupMember `
    -Identity $DGName `
    -Member $_.EmailAddress
}

Write-Host "Distribution List created and members added successfully."
