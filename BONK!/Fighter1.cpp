#include "Fighter1.h"
#include "DxLib.h"

Fighter1::Fighter1()
{
}

Fighter1::~Fighter1()
{
}

void Fighter1::Init()
{
	m_x = 100.0f; // 初期位置X
	m_y = 400.0f;   // 初期位置Y
	m_width = 50.0f; // 幅
	m_height = 100.0f; // 高さ
	m_ForwardSpeed = 5.0f; // 前進速度
	m_BackSpeed = 3.0f; // 後退速度
	m_Jump = -10.0f; // ジャンプ力
	m_air = false; // 空中状態フラグ
	m_isFacingRight = true; // 向きフラグ
}

void Fighter1::End()
{
}

void Fighter1::Update()
{
	// 移動処理
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
	// ジャンプ処理
	if (CheckHitKey(KEY_INPUT_W) && !m_air)
	{
		m_air = true;
		m_y += m_Jump;
	}
	// 重力処理
	if (m_air)
	{
		m_y += 0.5f; // 重力加速度
		if (m_y + m_height >= 510.0f) // 地面に着地した場合
		{
			m_y = 500 - m_height; // 床の高さ
			m_air = false;
		}
	}
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


