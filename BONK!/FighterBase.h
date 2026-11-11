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
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	float m_ForwardSpeed;
	float m_BackSpeed;
	float m_Jump;
	bool m_air;
	bool m_isGuarding;
	bool m_isFacingRight;
};