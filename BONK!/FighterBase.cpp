#include "FighterBase.h"

FighterBase::FighterBase():
    hp(100),
	m_x(0.0f),
	m_y(0.0f),
	m_gravity(0.5f),
	m_vy(0.0f),
	m_width(0.0f),
	m_height(0.0f),
	m_ForwardSpeed(5.0f),
	m_BackSpeed(3.0f),
	m_Jump(-60.0f),
	m_jumpDir(0),
	m_air(false),
	m_isGuarding(false),
	m_isFacingRight(true),
	m_color(0),
	m_keyRight(0),
	m_keyLeft(0),
	m_keyUp(0),
	m_keyAttack(0),
	m_isAttacking(false),
	m_attackFrame(0),
	m_attackHit(false),
	m_prevAttackKey(0),
	m_attackActiveStart(5),
	m_attackActiveEnd(8),
	m_attackTotal(20),
	m_attackDamage(5),
	m_attackW(40.0f),
	m_attackH(30.0f),
	m_attackOffsetY(20.0f)
{
}

FighterBase::~FighterBase()
{
}

void FighterBase::SetKeys(int right, int left, int up, int attack)
{
	m_keyRight = right;
	m_keyLeft = left;
	m_keyUp = up;
	m_keyAttack = attack;
}

void FighterBase::SetPosition(float x, bool isFacingRight)
{
	m_x = x;
	m_isFacingRight = isFacingRight;
}

void FighterBase::SetColor(int color)
{
	m_color = color;
}

void FighterBase::FaceTo(float targetX)
{
	// 空中や攻撃中は向きを変えない
	if (m_air == true || m_isAttacking == true)
	{
		return;
	}

	if (targetX > m_x)
	{
		m_isFacingRight = true;
	}
	else
	{
		m_isFacingRight = false;
	}
}

float FighterBase::GetX() const
{
	return m_x;
}

int FighterBase::GetHp() const
{
	return hp;
}

void FighterBase::TakeDamage(int damage)
{
	hp -= damage;
	if (hp < 0)
	{
		hp = 0;
	}
}

void FighterBase::GetBodyBox(float& left, float& top, float& right, float& bottom) const
{
	left = m_x;
	top = m_y;
	right = m_x + m_width;
	bottom = m_y + m_height;
}

bool FighterBase::IsAttackActive() const
{
	if (m_isAttacking == false)
	{
		return false;
	}
	if (m_attackFrame < m_attackActiveStart)
	{
		return false;
	}
	if (m_attackFrame >= m_attackActiveEnd)
	{
		return false;
	}
	return true;
}

void FighterBase::CalcAttackBox(float& left, float& top, float& right, float& bottom) const
{
	if (m_isFacingRight == true)
	{
		// 右向きなら体の右側に出す
		left = m_x + m_width;
		right = left + m_attackW;
	}
	else
	{
		// 左向きなら体の左側に出す
		right = m_x;
		left = right - m_attackW;
	}
	top = m_y + m_attackOffsetY;
	bottom = top + m_attackH;
}

bool FighterBase::GetAttackBox(float& left, float& top, float& right, float& bottom) const
{
	// 判定が出ていない、またはもう当たった攻撃は判定なし
	if (IsAttackActive() == false || m_attackHit == true)
	{
		return false;
	}
	CalcAttackBox(left, top, right, bottom);
	return true;
}

int FighterBase::GetAttackDamage() const
{
	return m_attackDamage;
}

void FighterBase::SetAttackHit()
{
	m_attackHit = true;
}
