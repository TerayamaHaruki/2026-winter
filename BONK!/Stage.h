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

    int m_groundY = 500; // 床の高さ

private:
    
};