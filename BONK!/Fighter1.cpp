#include "Fighter1.h"
#include "DxLib.h"

void Fighter1::Init()
{
}

void Fighter1::End()
{
}

void Fighter1::Update()
{
	// 移動処理
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_x += m_ForwardSpeed;
		m_isFacingRight = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_x -= m_BackSpeed;
		m_isFacingRight = false;
	}
	// ジャンプ処理
	if (CheckHitKey(KEY_INPUT_UP) && !m_air)
	{
		m_air = true;
		m_y += m_Jump;
	}
	// 重力処理
	if (m_air)
	{
		m_y += 0.5f; // 重力加速度
		if (m_y >= 0.0f) // 地面に着地した場合
		{
			m_y = 0.0f;
			m_air = false;
		}
	}
}	

void Fighter1::Draw()
{
	// プレイヤーの描画
	DrawBox(static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_x + m_width), static_cast<int>(m_y + m_height), GetColor(255, 0, 0), TRUE);
}


