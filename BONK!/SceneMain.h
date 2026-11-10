#pragma once

#include <memory>

class FighterBase;

class SceneMain
{
public:
    SceneMain();
    ~SceneMain();

    void Init();
    void End();

    void Update();
    void Draw();

private:
    int m_frameCount;

    // プレイヤー管理
    std::unique_ptr<FighterBase> m_player1;
    std::unique_ptr<FighterBase> m_player2;
};