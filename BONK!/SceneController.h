#pragma once
#include <memory>
#include <list>

class Scene;
class Input;

// シーンの切り替えと、現在のシーンの更新・描画を担当するクラス
class SceneController
{
public:
	// 全部のシーンを捨てて、newSceneだけにする(例: ポーズからタイトルに戻る)
	void ResetScene(std::shared_ptr<Scene> newScene);

	// いまのシーンをnewSceneに入れ替える(例: タイトルからゲームへ)
	void ChangeScene(std::shared_ptr<Scene> newScene);

	// いまのシーンの上にnewSceneを重ねる(例: ゲームの上にポーズ)
	void PushScene(std::shared_ptr<Scene> newScene);

	// 一番上のシーンを外す(例: ポーズをやめてゲームに戻る)
	void PopScene();

	// 一番上のシーンだけ更新する
	void Update(Input& input);

	// すべてのシーンを、下から順に描く(ポーズ中もゲーム画面が見えるように)
	void Draw();

private:
	std::list<std::shared_ptr<Scene>> m_scenes;
};
