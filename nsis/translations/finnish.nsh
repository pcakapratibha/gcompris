;;
;;  finish.nsh
;;
;;  Finish language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: "Toni_"Daigle"_Impiö" <toni.impio@pp1.inet.fi>
;;  Version 2
;;


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Vieraile GComprisin Windows -sivustolla"

; GCompris Section Prompts and Texts
!define GCOMPRIS_PROMPT_WIPEOUT			"Vanha GCompris-hakemistosi poistetaan. Tahdotko jatkaa?$\r$\rHuomio: Jokainen jälkeenpäin asennettu lisäosa poistetaan.$\rGComprisin käyttäjäasetuksissa ei tapahdu muutoksia."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Antamasti hakemisto on jo olemassa. Kaikki tiedot poistetaan $\r. Tahdotko jatkaa?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Asennuksen poistaja ei löytänyt reksiteristä tietoja GComprisista.$\rOn todennäköistä että joku muu käyttäjä on asentanut ohjelman."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Sinulla ei ole valtuuksia poistaa ohjelmaa."
