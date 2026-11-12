#pragma once

class FighterBase
{
public:
	FighterBase();
	virtual ~FighterBase();
	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	int hp;
	// 座標
	float m_x;
	float m_y;
	// 重力
	float m_gravity;
	// 縦方向の速度(上向きがマイナス)
	float m_vy;
	// サイズ
	float m_width;
	float m_height;
	// 移動速度
	float m_ForwardSpeed;
	float m_BackSpeed;
	// ジャンプ力
	float m_Jump;
	// 空中にいるかどうか
	bool m_air;
	// ガード中かどうか
	bool m_isGuarding;
	// 右向きかどうか
	bool m_isFacingRight;
};