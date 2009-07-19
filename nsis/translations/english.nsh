;;
;;  english.nsh
;;
;;  Default language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Version 3
;;  Note: If translating this file, replace "!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING"
;;  with "!define".

; Make sure to update the GCOMPRIS_MACRO_LANGUAGEFILE_END macro in
; langmacros.nsh when updating this file

; Startup Checks
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING InstallerIsRunning	"The installer is already running."
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING GcomprisIsRunning	"An instance of GCompris is currently running. Exit GCompris and then try again."

; Installer Finish Page
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING GcomprisFinishVisitWebSite	"Visit the Windows GCompris Web Page"

; GCompris Section Prompts and Texts
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING GcomprisPromptWipeout	"Your old GCompris directory is about to be deleted. Would you like to continue?$\r$\rNote: Any non-standard plugins that you may have installed will be deleted.$\rGCompris user settings will not be affected."
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING GcomprisPromptDirExists	"The installation directory you specified already exists. Any contents$\rwill be deleted. Would you like to continue?"

; Uninstall Section Prompts
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING unGcomprisUninstallError1	"The uninstaller could not find registry entries for GCompris.$\rIt is likely that another user installed this application."
!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING unGcomprisUninstallError2	"You do not have permission to uninstall this application."
