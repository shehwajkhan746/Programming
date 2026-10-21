# This script retrieves the members of a Dynamic Distribution Group (DDG) in Exchange and exports the list to a CSV file.
-------------------------------------------------------------------------------------------------------------------------

# Define the name of the Dynamic Distribution Group you want to retrieve members from
$DDG = Get-DynamicDistributionGroup "Dynamic Distribution Group Name"

# Get the members of the Dynamic Distribution Group using the RecipientPreviewFilter and OrganizationalUnit properties
Get-Recipient -RecipientPreviewFilter $DDG.RecipientFilter `
-OrganizationalUnit $DDG.RecipientContainer |
Select Name,DisplayName,PrimarySmtpAddress |

# Export the results to a CSV file
Export-Csv "C:\Users\sansari\Downloads\DDGMembers.csv" -NoTypeInformation