;;
;;  japanese.nsh
;;
;;  Japanese language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 932
;;
;;  Author: "Takeshi Kurosawa" <t-kuro@abox23.so-net.ne.jp>
;;  Version 2
;;


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Windows GComprisのWebページを訪れてください。"

; GCompris Section Prompts and Texts
!define GCOMPRIS_PROMPT_WIPEOUT			"古いGComprisのフォルダの削除に関して。続行しますか?$\r$\r注意: あなたのインストールしたすべての非標準なプラグインは削除されます。$\rGComprisの設定は影響を受けません。"
!define GCOMPRIS_PROMPT_DIR_EXISTS		"あなたの指定したインストール先のフォルダはすでに存在しています。内容はすべて$\r削除されます。続行しますか?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"アンインストーラはGComprisのレジストリエントリを発見できませんでした。$\rおそらく別のユーザにインストールされたでしょう。"
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"あなたはこのアプリケーションをアンインストールする権限を持っていません。"
