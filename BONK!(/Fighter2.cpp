#include "Fighter2.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
    constexpr float kMoveSpeed = 5.0f;
    constexpr int kFighterWidth = 60;
    constexpr int kFighterHeight = 100;
    constexpr int kGroundY = Game::kScreenHeight - 130;
}

Fighter2::Fighter2()
    : m_x(static_cast<float>(Game::kScreenWidth * 3 / 4))
    , m_y(static_cast<float>(kGroundY))
    , m_isMoving(false)
{
}

void Fighter2::Update()
{
    m_isMoving = false;

    if (CheckHitKey(KEY_INPUT_LEFT) != 0)
    {
        m_x -= kMoveSpeed;
        m_isMoving = true;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
    {
        m_x += kMoveSpeed;
        m_isMoving = true;
    }

    const float minX = static_cast<float>(kFighterWidth / 2);
    const float maxX = static_cast<float>(Game::kScreenWidth - kFighterWidth / 2);
    if (m_x < minX) m_x = minX;
    if (m_x > maxX) m_x = maxX;
}

void Fighter2::Draw() const
{
    const int left = static_cast<int>(m_x) - kFighterWidth / 2;
    const int top = static_cast<int>(m_y) - kFighterHeight;
    const int right = left + kFighterWidth;
    const int bottom = static_cast<int>(m_y);

    const unsigned int bodyColor = GetColor(255, 110, 90);
    const unsigned int outlineColor = GetColor(255, 235, 225);
    DrawBox(left, top, right, bottom, bodyColor, TRUE);
    DrawBox(left, top, right, bottom, outlineColor, FALSE);
    DrawString(left - 5, top - 22, "P2", GetColor(255, 255, 255));
}
