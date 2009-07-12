;;
;;  russian.nsh
;;
;;  Russian language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1251
;;
;;  Author: Tasselhof <anr@nm.ru>
;;  Version 2
;;


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Посетите веб-страницу GCompris для пользователей Windows."

; GCompris Section Prompts and Texts
!define GCOMPRIS_PROMPT_WIPEOUT			"Ваша старая директория GCompris будет фактически удалена. Вы желаете продолжить ?$\r$\rПримечание: Все нестандартные плагины которые Вы установили будут удалены..$\rПользовательские настройки GCompris не пострадают."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Директория, которую Вы указали для установки уже существует. Всё содержимое$\rбудет удалено. Вы желаете продолжить?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Программа удаления не может найти данные GCompris в регистре..$\rВероятно это приложение установил другой пользователь."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"У Вас нет прав на удаление этого приложения."
