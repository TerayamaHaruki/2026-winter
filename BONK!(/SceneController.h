#pragma once

#include <memory>

class Scene;

// 現在のシーンを所有し、シーンの開始・更新・描画・切り替えを管理する。
class SceneController
{
private:
    std::unique_ptr<Scene> m_currentScene;
    std::unique_ptr<Scene> m_nextScene;

    // Updateが終わったあとに、予約されているシーン切り替えを実行する。
    void ApplySceneChange();

public:
    SceneController() = default;
    ~SceneController();

    SceneController(const SceneController&) = delete;
    SceneController& operator=(const SceneController&) = delete;

    // 最初に表示するシーンを設定する。
    void Start(std::unique_ptr<Scene> firstScene);

    // 次に表示するシーンを予約する。
    void ChangeScene(std::unique_ptr<Scene> nextScene);

    // 現在のシーンを更新する。
    void Update();

    // 現在のシーンを描画する。
    void Draw();

    // ゲーム終了時に現在のシーンを終了する。
    void End();
};
