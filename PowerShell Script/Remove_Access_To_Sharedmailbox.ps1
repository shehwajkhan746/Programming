# Remove single/multiple users to single/multiple shared mailboxes with Full Access and Send As permissions. 

--------------------------------------------------------------------------------------------------------

# Define your users (can be one or multiple)
$Users = @(
    "user1@yourdomain.com",
    "user2@yourdomain.com"
)

# Define your target shared mailboxes
$SharedMailboxes = @(
    "shared1@yourdomain.com",
    "shared2@yourdomain.com"
)

# Loop through each mailbox and remove permissions to each user
foreach ($Mailbox in $SharedMailboxes) {
    foreach ($User in $Users) {
        Write-Host "Assigning permissions for $User on $Mailbox..." -ForegroundColor Cyan

        # Remove Full Access permission
        Remove-MailboxPermission -Identity $Mailbox -User $User `
            -AccessRights FullAccess -InheritanceType All -Confirm:$false

        # Remove Send As permission
        Remove-RecipientPermission -Identity $Mailbox -Trustee $User `
            -AccessRights SendAs -Confirm:$false
    }
}
