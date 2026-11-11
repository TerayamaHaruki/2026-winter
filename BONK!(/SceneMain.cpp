#include "SceneMain.h"
#include "SceneController.h"
#include "GameScene.h"
#include "DxLib.h"
#include "Mouse.h"
#include <memory>

SceneMain::SceneMain(SceneController& sceneController)
    : Scene(sceneController)
    , m_frameCount(0)
    , m_wasEnterPressed(false)
{
}

void SceneMain::Init()
{
    m_frameCount = 0;
    m_wasEnterPressed = false;
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
    ++m_frameCount;

    const bool isEnterPressed = CheckHitKey(KEY_INPUT_RETURN) != 0;
    // 押しっぱなしではなく、Enterを押した瞬間だけ反応させる。
    if (isEnterPressed && !m_wasEnterPressed)
    {
        m_sceneController.ChangeScene(std::make_unique<GameScene>(m_sceneController));
    }
    m_wasEnterPressed = isEnterPressed;
}

void SceneMain::Draw()
{
    DrawString(0, 0, "BONK! - TITLE / MAIN SCENE", GetColor(255, 255, 255));
    DrawFormatString(0, 24, GetColor(255, 255, 255), "FRAME: %d", m_frameCount);
    DrawFormatString(0, 48, GetColor(255, 255, 255), "MOUSE: (%5d, %5d)", Mouse::GetX(), Mouse::GetY());
    DrawString(0, 80, "Press ENTER: Go to GameScene", GetColor(255, 255, 0));
}
