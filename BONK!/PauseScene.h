#pragma once
#include "Scene.h"

// ポーズ画面(ゲームの上に重ねて表示する)
class PauseScene : public Scene
{
public:
	PauseScene(SceneController& controller);
	virtual ~PauseScene();

	virtual void Update(Input& input) override;
	virtual void Draw() override;

private:
	int m_cursor; // 0:つづける 1:タイトルにもどる
};
