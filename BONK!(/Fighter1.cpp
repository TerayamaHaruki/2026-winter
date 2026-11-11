#include "Fighter1.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
    constexpr float kMoveSpeed = 5.0f;
    constexpr int kFighterWidth = 60;
    constexpr int kFighterHeight = 100;
    constexpr int kGroundY = Game::kScreenHeight - 130;
}

Fighter1::Fighter1()
    : m_x(static_cast<float>(Game::kScreenWidth / 4))
    , m_y(static_cast<float>(kGroundY))
    , m_isMoving(false)
{
}

void Fighter1::Update()
{
    m_isMoving = false;

    if (CheckHitKey(KEY_INPUT_A) != 0)
    {
        m_x -= kMoveSpeed;
        m_isMoving = true;
    }
    if (CheckHitKey(KEY_INPUT_D) != 0)
    {
        m_x += kMoveSpeed;
        m_isMoving = true;
    }

    const float minX = static_cast<float>(kFighterWidth / 2);
    const float maxX = static_cast<float>(Game::kScreenWidth - kFighterWidth / 2);
    if (m_x < minX) m_x = minX;
    if (m_x > maxX) m_x = maxX;
}

void Fighter1::Draw() const
{
    const int left = static_cast<int>(m_x) - kFighterWidth / 2;
    const int top = static_cast<int>(m_y) - kFighterHeight;
    const int right = left + kFighterWidth;
    const int bottom = static_cast<int>(m_y);

    // キャラクター画像を接続するまでの仮表示。
    const unsigned int bodyColor = GetColor(70, 160, 255);
    const unsigned int outlineColor = GetColor(230, 240, 255);
    DrawBox(left, top, right, bottom, bodyColor, TRUE);
    DrawBox(left, top, right, bottom, outlineColor, FALSE);
    DrawString(left - 5, top - 22, "P1", GetColor(255, 255, 255));
}
