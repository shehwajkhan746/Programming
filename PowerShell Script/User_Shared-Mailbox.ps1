# Define your users (can be one or multiple)
$Users = @("user1@yourdomain.com", "user2@yourdomain.com")

# Define your target shared mailboxes
$SharedMailboxes = @("shared1@yourdomain.com", "shared2@yourdomain.com", "shared3@yourdomain.com")

# Loop through each mailbox and assign permissions to each user
foreach ($Mailbox in $SharedMailboxes) {
    foreach ($User in $Users) {
        Write-Host "Assigning permissions for $User on $Mailbox..." -ForegroundColor Cyan
        
        # Grant Full Access permission
        Add-MailboxPermission -Identity $Mailbox -User $User -AccessRights FullAccess -InheritanceType All -Confirm:$false
        
        # Grant Send As permission
        Add-RecipientPermission -Identity $Mailbox -Trustee $User -AccessRights SendAs -Confirm:$false
    }
}
