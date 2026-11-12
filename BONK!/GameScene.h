#pragma once
#include <memory>
#include "Stage.h"

class FighterBase;
class Stage;


class GameScene
{
public:
    GameScene();
    ~GameScene();

    void Init();
    void End();

    void Update();
    void Draw();

private:
    int m_frameCount;

    // プレイヤー管理
    std::unique_ptr<FighterBase> m_player1;
    std::unique_ptr<FighterBase> m_player2;
	// ステージ管理
    Stage m_stage;
};