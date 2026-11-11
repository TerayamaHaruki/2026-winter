#include "SceneController.h"
#include "Scene.h"
#include <utility>

SceneController::~SceneController()
{
    End();
}

void SceneController::Start(std::unique_ptr<Scene> firstScene)
{
    // Startを複数回呼んでも、前のシーンをきちんと終了させる。
    End();

    m_currentScene = std::move(firstScene);
    if (m_currentScene)
    {
        m_currentScene->Init();
    }
}

void SceneController::ChangeScene(std::unique_ptr<Scene> nextScene)
{
    // Update中に現在のシーンを破棄すると危険なので、切り替えだけ予約する。
    m_nextScene = std::move(nextScene);
}

void SceneController::ApplySceneChange()
{
    if (!m_nextScene)
    {
        return;
    }

    if (m_currentScene)
    {
        m_currentScene->End();
    }

    m_currentScene = std::move(m_nextScene);

    if (m_currentScene)
    {
        m_currentScene->Init();
    }
}

void SceneController::Update()
{
    if (m_currentScene)
    {
        m_currentScene->Update();
    }

    // シーン自身のUpdateが戻ってきてから切り替える。
    ApplySceneChange();
}

void SceneController::Draw()
{
    if (m_currentScene)
    {
        m_currentScene->Draw();
    }
}

void SceneController::End()
{
    // 予約中のシーンはまだInitされていないため、そのまま破棄してよい。
    m_nextScene.reset();

    if (m_currentScene)
    {
        m_currentScene->End();
        m_currentScene.reset();
    }
}
