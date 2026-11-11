#pragma once

#include "FighterBase.h"

// プレイヤー2。現在は移動と仮表示を実装している。
class Fighter2 final : public FighterBase
{
public:
    Fighter2();

    void Update() override;
    void Draw() const override;

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

private:
    float m_x;
    float m_y;
    bool m_isMoving;
};
