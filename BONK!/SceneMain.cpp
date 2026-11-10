#include "SceneMain.h"
#include "Fighter1.h"

SceneMain::SceneMain()
    : m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
    m_frameCount = 0;

    // プレイヤー生成
    m_player1 = std::make_unique<Fighter1>();
    m_player2 = std::make_unique<Fighter1>();
}

void SceneMain::Update()
{
    m_frameCount++;

    if (m_player1)
    {
        m_player1->Update();
    }

    if (m_player2)
    {
        m_player2->Update();
    }
}

void SceneMain::Draw()
{
    if (m_player1)
    {
        m_player1->Draw();
    }

    if (m_player2)
    {
        m_player2->Draw();
    }
}