#include "Fighter1.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kGroundY = 500.0f; // 床の高さ(Stageと同じ値)
}

Fighter1::Fighter1()
{
}

Fighter1::~Fighter1()
{
}

void Fighter1::Init()
{
	m_x = 100.0f; // 初期位置X
	m_width = 30.0f; // 幅
	m_height = 80.0f; // 高さ
	m_y = kGroundY - m_height; // 初期位置Y(足元が床に付く高さ)
	m_vy = 0.0f;
	m_ForwardSpeed = 5.0f; // 前進速度
	m_BackSpeed = 3.0f; // 後退速度
	m_Jump = -12.0f; // ジャンプ力
	m_air = false; // 空中状態フラグ
	m_isFacingRight = true; // 向きフラグ
}

void Fighter1::End()
{
}

void Fighter1::Update()
{
	// 地上にいるときの移動
	if (m_air == false)
	{
		if (CheckHitKey(KEY_INPUT_D))
		{
			m_x += m_ForwardSpeed;
			m_isFacingRight = true;
		}
		else if (CheckHitKey(KEY_INPUT_A))
		{
			m_x -= m_BackSpeed;
			m_isFacingRight = false;
		}
	}

	// ジャンプ(上キーを押した瞬間)
	if (CheckHitKey(KEY_INPUT_W) && m_air == false)
	{
		m_air = true;
		m_vy = m_Jump;

		if (CheckHitKey(KEY_INPUT_D))
		{
			// 上 + 前 = 前ジャンプ
			m_jumpDir = 1;
		}
		else if (CheckHitKey(KEY_INPUT_A))
		{
			// 上 + 後ろ = 後ろジャンプ
			m_jumpDir = -1;
		}
		else
		{
			// 上だけ = 垂直ジャンプ
			m_jumpDir = 0;
		}
	}

	// 空中にいるとき
	if (m_air == true)
	{
		// 横に進む(ジャンプした方向のまま)
		if (m_jumpDir == 1)
		{
			m_x += m_ForwardSpeed;
		}
		else if (m_jumpDir == -1)
		{
			m_x -= m_BackSpeed;
		}

		// 縦に進む(重力で少しずつ下向きの速度になる)
		m_vy += m_gravity;
		m_y += m_vy;

		// 床に着いたら着地
		if (m_y + m_height >= kGroundY)
		{
			m_y = kGroundY - m_height;
			m_vy = 0.0f;
			m_air = false;
			m_jumpDir = 0;
		}
	}

	// 画面の外に出ないようにする
	if (m_x < 0.0f)
	{
		m_x = 0.0f;
	}
	if (m_x + m_width > Game::kScreenWidth)
	{
		m_x = Game::kScreenWidth - m_width;
	}

	bool nowKey = CheckHitKey(KEY_INPUT_J) != 0;
	if (nowKey && !m_prevAttackKey == false && m_isAttacking == false && m_air == false)
	{
		m_isAttacking = true;
		m_attackFrame = 0;
		m_attackFrame = false;
	}
	m_prevAttackKey = nowKey;
}

void Fighter1::Draw()
{
	// プレイヤーの描画
	DrawBox(
		static_cast<int>(m_x),
		static_cast<int>(m_y),
		static_cast<int>(m_x + m_width),
		static_cast<int>(m_y + m_height),
		GetColor(255, 0, 0),
		TRUE
	);
}


