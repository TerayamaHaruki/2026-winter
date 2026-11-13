#pragma once
#include <memory>
#include "Stage.h"
#include "Scene.h"

class FighterBase;
class Stage;


class GameScene : public Scene
{
public:
    GameScene(SceneController& controller);
    ~GameScene();

    void Init();
    void End();

    virtual void Update(Input& input) override;
    virtual void Draw() override;

private:
    int m_frameCount;

    // プレイヤー管理
    std::unique_ptr<FighterBase> m_player1;
    std::unique_ptr<FighterBase> m_player2;
	// ステージ管理
    Stage m_stage;
};