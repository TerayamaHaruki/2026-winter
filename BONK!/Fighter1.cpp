#include "Fighter1.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kGroundY = 500.0f; // 床の高さ
	constexpr float kStandHeight = 80.0f;   // 立っているときの高さ
	constexpr float kCrouchHeight = 50.0f;  // しゃがんだときの高さ
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
	m_color = GetColor(255, 0, 0); // 体の色(赤)
}

void Fighter1::End()
{
}

void Fighter1::Update()
{
	// 前と後ろのキーを決める(向いている方向が「前」) 
	int forwardKey;
	int backKey;
	float dir; // 右向きなら1、左向きなら-1
	if (m_isFacingRight == true)
	{
		forwardKey = m_keyRight;
		backKey = m_keyLeft;
		dir = 1.0f;
	}
	else
	{
		forwardKey = m_keyLeft;
		backKey = m_keyRight;
		dir = -1.0f;
	}

	// 攻撃のフレームを進める 
	if (m_isAttacking == true)
	{
		m_attackFrame++;
		if (m_attackFrame >= m_attackTotal)
		{
			m_isAttacking = false; // 攻撃終わり
		}
	}

	// 攻撃を始める(キーを押した瞬間)
	int nowAttackKey = CheckHitKey(m_keyAttack);
	int nowStrongKey = CheckHitKey(m_keyStrong);

	// 弱攻撃
	if (nowAttackKey == 1 && m_prevAttackKey == 0 && m_isAttacking == false && m_air == false)
	{
		m_isAttacking = true;
		m_isStrongAttack = false;
		m_attackFrame = 0;
		m_attackHit = false;

		// 弱攻撃
		m_attackActiveStart = 5;  // 5フレーム目から判定が出る
		m_attackActiveEnd = 8;    // 8フレーム目の手前まで(3フレーム)
		m_attackTotal = 20;       // 20フレームで終わる
		m_attackDamage = 5;       // ダメージ
		m_attackW = 40.0f;        // 判定の幅
		m_attackH = 30.0f;        // 判定の高さ
		m_attackOffsetY = 20.0f;  // 体の上から20px下
	}
	// 強攻撃
	else if (nowStrongKey == 1 && m_prevStrongKey == 0 && m_isAttacking == false && m_air == false)
	{
		m_isAttacking = true;
		m_isStrongAttack = true;
		m_attackFrame = 0;
		m_attackHit = false;

		// 強攻撃のデータ
		m_attackActiveStart = 12; // 12フレーム目から判定が出る(遅い)
		m_attackActiveEnd = 16;   // 16フレーム目の手前まで(4フレーム)
		m_attackTotal = 40;       // 40フレームで終わる(硬直が長い)
		m_attackDamage = 10;      // ダメージ
		m_attackW = 60.0f;        // 判定の幅(長い)
		m_attackH = 40.0f;        // 判定の高さ
		m_attackOffsetY = 15.0f;  // 体の上から15px下
	}
	// 空中弱
	else if (nowAttackKey == 1 && m_prevAttackKey == 0 && m_isAttacking == false && m_air == true)
	{
		m_isAttacking = true;
		m_isStrongAttack = false;
		m_attackFrame = 0;
		m_attackHit = false;

		//空中弱
		m_attackActiveStart = 4;
		m_attackActiveEnd = 12;
		m_attackTotal = 20;
		m_attackDamage = 7;
		m_attackW = 30.0f;
		m_attackH = 20.0f;
		m_attackOffsetY = 70.0f;
	}
	m_prevAttackKey = nowAttackKey;
	m_prevStrongKey = nowStrongKey;

	// しゃがみ
	if (m_air == false && m_isAttacking == false)
	{
		if (CheckHitKey(m_keyDown))
		{
			m_isCrouching = true;
			m_height = kCrouchHeight;
		}
		else
		{
			m_isCrouching = false;
			m_height = kStandHeight;
		}
		m_y = kGroundY - m_height;
	}

	// 地上にいるときの移動(攻撃中は動けない) 
	if (m_air == false && m_isAttacking == false && m_isCrouching == false)
	{
		if (CheckHitKey(forwardKey))
		{
			m_x += dir * m_ForwardSpeed;
		}
		else if (CheckHitKey(backKey))
		{
			m_x -= dir * m_BackSpeed;
		}
	}

	// ジャンプ(上キーを押した瞬間) 
	if (CheckHitKey(m_keyUp) && m_air == false && m_isAttacking == false)
	{
		m_air = true;
		m_vy = m_Jump;

		if (CheckHitKey(forwardKey))
		{
			// 上 + 前 = 前ジャンプ
			m_jumpDir = 1;
		}
		else if (CheckHitKey(backKey))
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
			m_x += dir * m_ForwardSpeed;
		}
		else if (m_jumpDir == -1)
		{
			m_x -= dir * m_BackSpeed;
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
}

void Fighter1::Draw()
{
	// プレイヤーの描画
	DrawBox(
		static_cast<int>(m_x),
		static_cast<int>(m_y),
		static_cast<int>(m_x + m_width),
		static_cast<int>(m_y + m_height),
		m_color,
		TRUE
	);

	// 攻撃判定が出ている間は、黄色い枠で見えるようにする(確認用)
	if (IsAttackActive() == true)
	{
		float left;
		float top;
		float right;
		float bottom;
		CalcAttackBox(left, top, right, bottom);

		// 弱攻撃は黄色、強攻撃はオレンジ
		int boxColor = GetColor(255, 255, 0);
		if (m_isStrongAttack == true)
		{
			boxColor = GetColor(255, 140, 0);
		}
		DrawBox(
			static_cast<int>(left),
			static_cast<int>(top),
			static_cast<int>(right),
			static_cast<int>(bottom),
			boxColor,
			FALSE
		);
	}
}


