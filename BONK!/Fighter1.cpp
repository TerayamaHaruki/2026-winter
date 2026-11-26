#include "Fighter1.h"
#include "Input.h"
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

void Fighter1::Update(Input& input)
{
	// 前と後ろのキーを決める(向いている方向が「前」) 
	std::string forwardName;
	std::string backName;
	float dir; // 右向きなら1、左向きなら-1
	if (m_isFacingRight == true)
	{
		forwardName = m_prefix + "right";
		backName = m_prefix + "left";
		dir = 1.0f;
	}
	else
	{
		forwardName = m_prefix + "left";
		backName = m_prefix + "right";
		dir = -1.0f;
	}

	// 入力を最初にまとめて調べる(キーボードもパッドも Input がまとめてくれる)
	bool forwardPressed = input.IsPressed(forwardName);
	bool backPressed = input.IsPressed(backName);
	bool upPressed = input.IsPressed(m_prefix + "up");
	bool downPressed = input.IsPressed(m_prefix + "down");
	bool weakTriggered = input.IsTriggered(m_prefix + "weak");     // 押した瞬間
	bool strongTriggered = input.IsTriggered(m_prefix + "strong"); // 押した瞬間

	// 攻撃のフレームを進める 
	if (m_isAttacking == true)
	{
		m_attackFrame++;
		if (m_attackFrame >= m_attackTotal)
		{
			m_isAttacking = false; // 攻撃終わり
		}
	}

	// 弱攻撃
	if (weakTriggered && m_isAttacking == false && m_air == false && m_isCrouching == false)
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
		m_attackW = 35.0f;        // 判定の幅
		m_attackH = 25.0f;        // 判定の高さ
		m_attackOffsetY = 20.0f;  // 体の上から20px下
	}
	// 強攻撃
	else if (strongTriggered && m_isAttacking == false && m_air == false && m_isCrouching == false)
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
		m_attackW = 50.0f;        // 判定の幅(長い)
		m_attackH = 30.0f;        // 判定の高さ
		m_attackOffsetY = 15.0f;  // 体の上から15px下
	}
	// しゃがみ弱
	else if (weakTriggered && m_isAttacking == false && m_air == false && m_isCrouching == true)
	{
		m_isAttacking = true;
		m_isStrongAttack = false;
		m_attackFrame = 0;
		m_attackHit = false;

		// 弱攻撃
		m_attackActiveStart = 4;  
		m_attackActiveEnd = 7;    
		m_attackTotal = 19;       
		m_attackDamage = 4;       
		m_attackW = 30.0f;        
		m_attackH = 20.0f;        
		m_attackOffsetY = 20.0f; 
	}
	// 空中弱
	else if (weakTriggered && m_isAttacking == false && m_air == true)
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
		m_attackOffsetY = 45.0f;
	}
	
	// しゃがみ
	if (m_air == false && m_isAttacking == false)
	{
		if (downPressed)
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
		if (forwardPressed)
		{
			m_x += dir * m_ForwardSpeed;
		}
		else if (backPressed)
		{
			m_x -= dir * m_BackSpeed;
		}
	}

	// ジャンプ(上キーを押した瞬間) 
	if (upPressed && m_air == false && m_isAttacking == false)
	{
		m_air = true;
		m_vy = m_Jump;
		m_height = kCrouchHeight;

		if (forwardPressed)
		{
			// 上 + 前 = 前ジャンプ
			m_jumpDir = 1;
		}
		else if (backPressed)
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


