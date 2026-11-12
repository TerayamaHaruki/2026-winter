#include "FighterBase.h"

FighterBase::FighterBase():
    hp(100),
	m_x(0.0f),
	m_y(0.0f),
	m_gravity(0.5f),
	m_width(0.0f),
	m_height(0.0f),
	m_ForwardSpeed(5.0f),
	m_BackSpeed(3.0f),
	m_Jump(-12.0f),
	m_air(false),
	m_isGuarding(false),
	m_isFacingRight(true)
{
}

FighterBase::~FighterBase()
{
}