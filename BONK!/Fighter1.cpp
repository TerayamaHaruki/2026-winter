#include "Fighter1.h"
#include "DxLib.h"

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
		m_vy = m_Jump; // 上向きの初速を与える
	}
	// 重力処理
	if (m_air)
	{
		m_vy += m_gravity; // 毎フレーム速度に重力を足す
		m_y += m_vy;       // 速度の分だけ移動
		if (m_y + m_height >= kGroundY) // 地面に着地した場合
		{
			m_y = kGroundY - m_height; // 足元を床に合わせる
			m_vy = 0.0f;
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


