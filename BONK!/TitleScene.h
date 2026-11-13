#pragma once
#include "Scene.h"

// タイトル画面
class TitleScene : public Scene
{
public:
	TitleScene(SceneController& controller);
	virtual ~TitleScene();

	virtual void Update(Input& input) override;
	virtual void Draw() override;

private:
	int m_frame; // 点滅用に、経過フレームを数える
};
