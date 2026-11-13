#pragma once

// プロトタイプ宣言(名前だけ知らせておく。中身はcppで#includeする)
class SceneController;
class Input;

// すべてのシーン(タイトル、ゲーム、ポーズ...)の親になるクラス
class Scene
{
public:
	Scene(SceneController& controller);
	virtual ~Scene();

	// 毎フレーム呼ばれる。状態を更新する
	virtual void Update(Input& input) = 0;
	// 毎フレーム呼ばれる。画面に描く
	virtual void Draw() = 0;

protected:
	// シーンを切り替えるときに使う
	SceneController& m_controller;
};
