#include "TitleScene.h"
#include "SceneController.h"
#include "GameScene.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"
#include <cstring>
#include <memory>

namespace
{
	// 画面の中央にそろえて文字を描く
	void DrawCenterString(int y, const char* text, unsigned int color)
	{
		int width = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));
		DrawString((Game::kScreenWidth - width) / 2, y, text, color);
	}
}

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller),
	m_frame(0)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(Input& input)
{
	m_frame++;

	// Enterキーでゲームを始める
	if (input.IsTriggered("ok"))
	{
		// シーンを入れ替えると、このTitleSceneは消える。
		// そのあとは何もせず、すぐreturnする
		m_controller.ChangeScene(std::make_shared<GameScene>(m_controller));
		return;
	}
}

void TitleScene::Draw()
{
	// 背景
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(20, 24, 48), TRUE);

	// タイトル
	SetFontSize(96);
	DrawCenterString(200, "BONK!", GetColor(242, 184, 75));

	// 30フレームごとに、出たり消えたりする
	SetFontSize(32);
	if ((m_frame / 30) % 2 == 0)
	{
		DrawCenterString(450, "PRESS ENTER", GetColor(255, 255, 255));
	}

	// 操作説明
	SetFontSize(20);
	DrawCenterString(580, "1P : A D move / W jump / J attack", GetColor(180, 186, 220));
	DrawCenterString(612, "2P : Left Right move / Up jump / , attack", GetColor(180, 186, 220));
	DrawCenterString(644, "P : pause     ESC : quit", GetColor(180, 186, 220));

	// 文字の大きさを元に戻す
	SetFontSize(16);
}
