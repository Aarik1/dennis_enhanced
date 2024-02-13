; Dennis Installer
; Based off the modern ui installer examples.
; VERY MESSY!!!!!

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "Dennis Enhanced Edition"
  OutFile "DennisEnhancedInstaller.exe"
  Unicode True

  ;Default installation folder
  InstallDir "$PROGRAMFILES\Dennis Enhanced Edition"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\Dennis Enhanced Edition" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Variables

  Var StartMenuFolder

;--------------------------------
;Interface Settings

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "installer.bmp" ; optional
  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "license.txt"
  ;!insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Dennis Enhanced Edition" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Dummy Section" SecDummy

  SetRegView 64

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  
  File "InstallerFiles\Dennis.exe"
  File "InstallerFiles\Dennis_Watcher.exe"
  File "InstallerFiles\dtalk_us.dic"
  
  ;Store installation folder
  WriteRegStr HKLM "Software\Dennis Enhanced Edition" "" $INSTDIR
  WriteRegStr HKLM "Software\Dennis Enhanced Edition" "DennisExe" "$INSTDIR/Dennis.exe"
  
  ;Run key
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" \
	"DennisEnhancedEdition" "$INSTDIR\Dennis_Watcher.exe"
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  ; Uninstall information
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"DisplayName" "Dennis Enhanced Edition"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"DisplayVersion" "0.1.2"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"DisplayIcon" "$INSTDIR\Dennis.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition" \
	"Publisher" "Joe's Sewer Dungeon"
  
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
SectionEnd

Function .onInit
	;SetRegView 64
FunctionEnd

Function .onInstSuccess
	;Exec `schtasks /create /sc onlogon /tn "DennisEnhancedEditionWatcher" /tr "'$INSTDIR\Dennis_Watcher.exe'"`
	Exec "$INSTDIR\Dennis_Watcher.exe"
FunctionEnd

;--------------------------------
;Descriptions

  ;Language strings
  ;LangString DESC_SecDummy ${LANG_ENGLISH} "A test section."

  ;Assign language strings to sections
 ; !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
   ; !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
  ;!insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"
  
  SetRegView 64
  
  ExecWait 'taskkill /f /t /im Dennis_Watcher.exe'
  ExecWait 'taskkill /f /t /im Dennis.exe'
  ;ExecWait 'schtasks /delete /tn "DennisEnhancedEditionWatcher" /f'	

  ClearErrors
  ;DeleteRegValue HKLM "Software\Dennis Enhanced Edition" "DennisExe"
  DeleteRegKey HKLM "SOFTWARE\Dennis Enhanced Edition"
  
  IfErrors 0 +2
	MessageBox MB_OK "Failed to delete registry keys1"
  
  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\DennisEnhancedEdition"
  DeleteRegValue HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "DennisEnhancedEdition"

  IfErrors 0 +2
	MessageBox MB_OK "Failed to delete registry keys2"

  ;ADD YOUR OWN FILES HERE...
  
  Delete "$INSTDIR\Dennis.exe"
  Delete "$INSTDIR\dtalk_us.dic"
  Delete "$INSTDIR\Dennis_Watcher.exe"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  

  
SectionEnd