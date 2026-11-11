#pragma once

class SceneController;

// すべてのシーンが共通して持つ機能を定義する基底クラス。
class Scene
{
protected:
    // シーンから次のシーンへの切り替えを依頼するための参照。
    SceneController& m_sceneController;

public:
    explicit Scene(SceneController& sceneController)
        : m_sceneController(sceneController)
    {
    }

    virtual ~Scene() = default;

    // シーン開始時に一度だけ呼ばれる。
    virtual void Init() = 0;

    // シーン終了時に一度だけ呼ばれる。
    virtual void End() = 0;

    // 毎フレーム呼ばれる更新処理。
    virtual void Update() = 0;

    // 毎フレーム呼ばれる描画処理。
    virtual void Draw() = 0;
};
