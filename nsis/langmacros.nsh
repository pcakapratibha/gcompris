;;
;; Windows Gcompris NSIS installer language macros
;;

!macro GCOMPRIS_MACRO_LANGSTRING_INSERT LABEL LANG
  LangString "${LABEL}" "${LANG_${LANG}}" "${${LABEL}}"
  !undef "${LABEL}"
!macroend

!macro GCOMPRIS_MACRO_LANGUAGEFILE_BEGIN LANG
  !define CUR_LANG "${LANG}"
!macroend

!macro GCOMPRIS_MACRO_LANGUAGEFILE_END
  !define INSERT_DEFAULT
  !include "${GCOMPRIS_DEFAULT_LANGFILE}"
  !undef INSERT_DEFAULT

  ; GCOMPRIS Language file Version 3
  ; String labels should match those from the default language file.

  ; Startup checks
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT InstallerIsRunning		${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisIsRunning		${CUR_LANG}

  ; License Page
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisLicenseButton		${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisLicenseBottomText	${CUR_LANG}

  ; Components Page
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisSectionTitle		${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisSectionDescription	${CUR_LANG}

  ; Installer Finish Page
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisFinishVisitWebSite	${CUR_LANG}

  ; Gcompris Section Prompts and Texts
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisUninstallDesc	${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisPromptWipeout	${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT GcomprisPromptDirExists	${CUR_LANG}

  ; Uninstall Section Prompts
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT unGcomprisUninstallError1	${CUR_LANG}
  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT unGcomprisUninstallError2	${CUR_LANG}

  !undef CUR_LANG
!macroend

!macro GCOMPRIS_MACRO_INCLUDE_LANGFILE LANG FILE
  !insertmacro GCOMPRIS_MACRO_LANGUAGEFILE_BEGIN "${LANG}"
  !include "${FILE}"
  !insertmacro GCOMPRIS_MACRO_LANGUAGEFILE_END
!macroend
