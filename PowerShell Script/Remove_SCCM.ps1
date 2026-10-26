


Function Test-RemoveRegistryPath {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path
    )
    if (Test-Path -Path $Path -PathType Any) {
        Write-Host "Registry path found: $Path. Removing..." -ForegroundColor Yellow
        try {
            Remove-Item -Path $Path -Recurse -Force -ErrorAction Stop
            Write-Host "Registry path removed: $Path" -ForegroundColor Green
        } catch {
            Write-Warning "Failed to remove  $Path : $_"
        }
    } else {
        Write-Host "Path not found: $Path" -ForegroundColor DarkGray
        return 0
    }
}
#this function checks for the existence of the file system path and then logs if it's found then deletes the path
Function Test-RemoveFilePath {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path
    )
    if (Test-Path -Path $Path) {
        Write-Host "File system path found: $Path. Removing..." -ForegroundColor Yellow
        try {
            Remove-Item -Path $Path -Recurse -Force -Confirm:$false -ErrorAction Stop
            Write-Host "File system path removed: $Path" -ForegroundColor Green
        } catch {
            Write-Warning "Failed to remove file system path $Path : $_"
        }
    } else {
        Write-Host "File system path not found: $Path" -ForegroundColor DarkGray
    }
}
$ccmSetupPath = "$($Env:WinDir)\CCMSetup\CCMSetup.exe"
# Check if the CCMSetup.exe file exists
if (Test-Path -Path $ccmSetupPath) {
    Write-Host "CCMSetup.exe found at $ccmSetupPath. Proceeding with uninstallation of SCCM client."
    # Execute the uninstallation command
    Start-Process -FilePath $ccmSetupPath -ArgumentList "/uninstall", "/forceuninstall" -Wait
    Write-Host "SCCM client uninstallation process initiated at $($Env:WinDir)."
} else {
    Write-Host "CCMSetup.exe not found at $ccmSetupPath. SCCM client may not be installed on this machine."
}
######### file ops
# Delete SCCM Client installation folder
Test-RemoveFilePath -Path "$($Env:WinDir)\CCM"
# Delete SCCM Client Cache folder
Test-RemoveFilePath -Path "$($Env:WinDir)\CCMSetup"
# Delete SCCM Client Setup files
Test-RemoveFilePath -Path "$($Env:WinDir)\CCMCache"
# Delete certificate GUID and SMS GUID file
Test-RemoveFilePath -Path "$($Env:WinDir)\smscfg.ini"
######### registry cleanup
# Delete the certificate itself
Test-RemoveRegistryPath -Path 'HKLM:\Software\Microsoft\SystemCertificates\SMS\Certificates\*'
# Remove all registry keys associated with the SCCM Client
Test-RemoveRegistryPath -Path 'HKLM:\SOFTWARE\Microsoft\CCM'
Test-RemoveRegistryPath -Path 'HKLM:\SOFTWARE\Wow6432Node\Microsoft\CCM'
Test-RemoveRegistryPath -Path 'HKLM:\SOFTWARE\Microsoft\SMS'
Test-RemoveRegistryPath -Path 'HKLM:\SOFTWARE\Wow6432Node\Microsoft\SMS'
Test-RemoveRegistryPath -Path 'HKLM:\Software\Microsoft\CCMSetup'
Test-RemoveRegistryPath -Path 'HKLM:\Software\Wow6432Node\Microsoft\CCMSetup'
# Remove the service from "Services"
Test-RemoveRegistryPath -Path 'HKLM:\SYSTEM\CurrentControlSet\Services\CcmExec'
Test-RemoveRegistryPath -Path 'HKLM:\SYSTEM\CurrentControlSet\Services\ccmsetup'
#Delete the WUServer registry value to reset Windows Update to use default Microsoft servers
Remove-ItemProperty -Path "HKLM:\SOFTWARE\Policies\Microsoft\Windows\WindowsUpdate" -Name "WUServer" -ErrorAction SilentlyContinue
# Optionally, also delete the WUStatusServer if it exists
Remove-ItemProperty -Path "HKLM:\SOFTWARE\Policies\Microsoft\Windows\WindowsUpdate" -Name "WUStatusServer" -ErrorAction SilentlyContinue
### Remove the WMI classes associated with the SCCM Client
# Remove the Namespaces from the WMI repository
Get-CimInstance  -query  "Select * From __Namespace Where Name='CCM'"  -Namespace  "root"  |  Remove-CimInstance  -Verbose  -Confirm:$false
Get-CimInstance  -query  "Select * From __Namespace Where Name='CCMVDI'"  -Namespace  "root"  |  Remove-CimInstance  -Verbose  -Confirm:$false
Get-CimInstance  -query  "Select * From __Namespace Where Name='SmsDm'"  -Namespace  "root"  |  Remove-CimInstance  -Verbose  -Confirm:$false
Get-CimInstance  -query  "Select * From __Namespace Where Name='sms'"  -Namespace  "root\cimv2"  |  Remove-CimInstance  -Verbose  -Confirm:$false