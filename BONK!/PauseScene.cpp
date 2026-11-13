#include "PauseScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"
#include <cstring>
#include <memory>

namespace
{
	constexpr int kItemNum = 2; // 項目の数

	// 画面の中央にそろえて文字を描く
	void DrawCenterString(int y, const char* text, unsigned int color)
	{
		int width = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));
		DrawString((Game::kScreenWidth - width) / 2, y, text, color);
	}
}

PauseScene::PauseScene(SceneController& controller) :
	Scene(controller),
	m_cursor(0)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(Input& input)
{
	// Pキーをもう一度押すと、ゲームに戻る
	if (input.IsTriggered("pause"))
	{
		m_controller.PopScene(); // このPauseSceneは消える。すぐreturn
		return;
	}

	// 上下キーでカーソルを動かす(端まで行ったら反対側へ)
	if (input.IsTriggered("up"))
	{
		m_cursor = (m_cursor + kItemNum - 1) % kItemNum;
	}
	if (input.IsTriggered("down"))
	{
		m_cursor = (m_cursor + 1) % kItemNum;
	}

	// Enterキーで決定
	if (input.IsTriggered("ok"))
	{
		if (m_cursor == 0)
		{
			// つづける
			m_controller.PopScene();
			return;
		}
		else
		{
			// タイトルにもどる(すべてのシーンを捨てて、タイトルだけにする)
			m_controller.ResetScene(std::make_shared<TitleScene>(m_controller));
			return;
		}
	}
}

void PauseScene::Draw()
{
	// 画面全体を、半透明の黒でおおう
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(64);
	DrawCenterString(180, "PAUSE", GetColor(242, 184, 75));

	SetFontSize(32);
	unsigned int white = GetColor(255, 255, 255);
	unsigned int gold = GetColor(242, 184, 75);

	// えらんでいる項目は金色にして、先頭に > を付ける
	DrawCenterString(320, m_cursor == 0 ? "> CONTINUE" : "  CONTINUE", m_cursor == 0 ? gold : white);
	DrawCenterString(380, m_cursor == 1 ? "> BACK TO TITLE" : "  BACK TO TITLE", m_cursor == 1 ? gold : white);

	SetFontSize(20);
	DrawCenterString(500, "Up Down : select     Enter : decide     P : back", GetColor(180, 186, 220));

	SetFontSize(16);
}
