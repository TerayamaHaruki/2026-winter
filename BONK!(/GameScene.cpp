#include "GameScene.h"
#include "SceneController.h"
#include "SceneMain.h"
#include "Fighter1.h"
#include "Fighter2.h"
#include "DxLib.h"
#include "Game.h"
#include <memory>

GameScene::GameScene(SceneController& sceneController)
    : Scene(sceneController)
    , m_frameCount(0)
    , m_wasBackspacePressed(false)
{
}

GameScene::~GameScene() = default;

void GameScene::Init()
{
    m_frameCount = 0;
    m_wasBackspacePressed = false;
    m_player1 = std::make_unique<Fighter1>();
    m_player2 = std::make_unique<Fighter2>();
}

void GameScene::End()
{
    // unique_ptrをresetすると、所有しているファイターがここで破棄される。
    m_player1.reset();
    m_player2.reset();
}

void GameScene::Update()
{
    ++m_frameCount;

    if (m_player1)
    {
        m_player1->Update();
    }
    if (m_player2)
    {
        m_player2->Update();
    }

    const bool isBackspacePressed = CheckHitKey(KEY_INPUT_BACK) != 0;
    if (isBackspacePressed && !m_wasBackspacePressed)
    {
        m_sceneController.ChangeScene(std::make_unique<SceneMain>(m_sceneController));
    }
    m_wasBackspacePressed = isBackspacePressed;
}

void GameScene::Draw()
{
    DrawString(0, 0, "BONK! - GAME SCENE", GetColor(255, 255, 255));
    DrawFormatString(0, 24, GetColor(255, 255, 255), "FRAME: %d", m_frameCount);
    DrawString(0, 56, "P1 : A / D", GetColor(255, 255, 0));
    DrawString(0, 80, "P2 : LEFT / RIGHT", GetColor(255, 180, 150));
    DrawString(0, 104, "BACKSPACE : Return to Main Scene", GetColor(255, 255, 0));

    // 仮のHP表示。現在は見た目だけで、ダメージ処理とは未接続。
    const unsigned int frameColor = GetColor(235, 235, 235);
    const unsigned int p1Color = GetColor(70, 160, 255);
    const unsigned int p2Color = GetColor(255, 110, 90);
    DrawString(40, 135, "P1 HP", GetColor(255, 255, 255));
    DrawBox(40, 158, 440, 178, frameColor, FALSE);
    DrawBox(42, 160, 438, 176, p1Color, TRUE);
    DrawString(Game::kScreenWidth - 440, 135, "P2 HP", GetColor(255, 255, 255));
    DrawBox(Game::kScreenWidth - 440, 158, Game::kScreenWidth - 40, 178, frameColor, FALSE);
    DrawBox(Game::kScreenWidth - 438, 160, Game::kScreenWidth - 42, 176, p2Color, TRUE);

    // ステージの仮の床ライン。
    DrawLine(0, Game::kScreenHeight - 130, Game::kScreenWidth, Game::kScreenHeight - 130, GetColor(180, 180, 180));

    if (m_player1)
    {
        m_player1->Draw();
    }
    if (m_player2)
    {
        m_player2->Draw();
    }
}
