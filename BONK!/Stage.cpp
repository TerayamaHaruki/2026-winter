#include "Stage.h"
#include "DxLib.h"
#include "Game.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
    m_groundY = 500;
}

void Stage::End()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
    DrawLine(
        0,
        m_groundY,
        Game::kScreenWidth,
        m_groundY,
        GetColor(255, 255, 255),
        3
    );
}