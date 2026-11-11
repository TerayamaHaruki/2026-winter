#pragma once

class Stage
{
public:
    Stage();
    virtual ~Stage();

    void Init();
    void End();
    void Update();
    void Draw();

private:
    int m_groundY; // 床の高さ
};