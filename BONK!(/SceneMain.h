#pragma once

#include "Scene.h"

class SceneMain : public Scene
{
public:
    explicit SceneMain(SceneController& sceneController);
    ~SceneMain() override = default;

    void Init() override;
    void End() override;
    void Update() override;
    void Draw() override;

private:
    int m_frameCount;
    bool m_wasEnterPressed;
};
