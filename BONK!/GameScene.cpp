#include "GameScene.h"
#include "Fighter1.h"
#include "DxLib.h"

GameScene::GameScene()
    : m_frameCount(0)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
    m_frameCount = 0;
    m_stage.Init();
    // プレイヤー生成
    m_player1 = std::make_unique<Fighter1>();
    m_player2 = std::make_unique<Fighter1>();

	// プレイヤー初期化
	m_player1->Init();
	m_player2->Init();
}

void GameScene::End()
{
	m_player1.reset();
	m_player2.reset();
}

void GameScene::Update()
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

void GameScene::Draw()
{
	m_stage.Draw();
    if (m_player1)
    {
        m_player1->Draw();
    }

    if (m_player2)
    {
        m_player2->Draw();
    }
}