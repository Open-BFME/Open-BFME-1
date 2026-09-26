' Copyright (c) Microsoft Corporation. All rights reserved.
' This utility will install the Microsoft.WindowsMediaServices.dll to the GAC.
' If it does not, verify the location of Microsoft.WindowsMediaServices.dll and gacutil.exe.
' It will also register the type library, WMSServerTypeLib.dll,  using RegSvr32.exe.
'

' Create default path to gacutil and verify with user.
' The paths may vary depending on your installation of Microsoft .NET Frameworks.
'
MsgBox("This utility will add the PIA to the GAC, and register the type library.")


gacPath = "C:\Program Files\Microsoft Visual Studio .NET\FrameworkSDK\Bin\" 
gacPath = InputBox("Please verify the path to Gacutil","Path to Gacutil",gacPath)

'
' Create default path to Microsoft.WindowsMediaServices.dll and verify with user.
'
sdkPath = "C:\Program Files\Microsoft SDK\include\"
sdkPath = InputBox("Please type the path to Microsoft.WindowsMediaServices.dll.","Path to Microsoft.WindowsMediaServices.dll",sdkPath)

'
' Command to keep box open.
goodBye = " & ECHO. & PAUSE & EXIT"

'
' Create final gacutil path
gacPath =  chr(34) + gacPath + "gacutil.exe" + chr(34) + " /i " + chr(34) + sdkPath + "Microsoft.WindowsMediaServices.dll" + chr(34)

'
' Add the paths together and add commands to keep display open
fullPath = "%COMSPEC% /k " + chr(34) + gacPath + " & ECHO. & "+ "regsvr32.exe " + chr(34) + sdkPath + "WMSServerTypeLib.dll" + chr(34) + goodBye  + chr(34)

'
' Create object for command.
Set objShell = CreateObject("WScript.Shell")

'
' Register the DLL and add it to the GAC
objShell.Run fullPath 
