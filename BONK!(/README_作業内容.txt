BONK! シーン管理・2人プレイヤー仮実装版

【今回までの変更】
・Scene / SceneController：シーンの生成・更新・描画・切り替えを管理
・SceneMain：EnterでGameSceneへ切り替え
・GameScene：BackspaceでSceneMainへ戻る
・FighterBase：ファイター共通インターフェース
・Fighter1：A/Dで移動するPlayer1の仮実装
・Fighter2：左右矢印で移動するPlayer2の仮実装
・GameScene：unique_ptrでP1/P2を所有し、シーン終了時に解放
・HPバーは現時点では見た目だけの仮表示（ダメージ処理とは未接続）
・Visual Studioプロジェクト／フィルターにFighter2を登録

【操作】
タイトル画面：Enterでゲーム画面へ
ゲーム画面：P1はA/D、P2は←/→で左右移動
ゲーム画面：Backspaceでタイトル画面へ
Escape：アプリ終了

【現在の未実装項目】
キャラクター画像・アニメーション、ジャンプ、攻撃、ガード、当たり判定、実際のHP/SP管理、勝敗判定はまだ接続していません。

【ビルド確認】
DxLib関数を簡易スタブに置き換えたC++構文チェックを行うこと。これはVisual Studio＋本物のDxLibでのビルド・実行確認の代わりにはなりません。

【復元】
問題があれば、別途保存したBONK_before_scene_implementation_2026-11-11.zipを展開して元の状態に戻してください。
