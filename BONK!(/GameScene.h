#pragma once

#include "Scene.h"
#include <memory>

class FighterBase;

class GameScene : public Scene
{
public:
    explicit GameScene(SceneController& sceneController);
    ~GameScene() override;

    void Init() override;
    void End() override;
    void Update() override;
    void Draw() override;

private:
    int m_frameCount;
    bool m_wasBackspacePressed;

    // GameSceneがプレイヤーを所有する。シーン終了時に自動で解放される。
    std::unique_ptr<FighterBase> m_player1;
    std::unique_ptr<FighterBase> m_player2;
};
