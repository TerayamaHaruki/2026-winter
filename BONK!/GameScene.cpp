#include "GameScene.h"
#include "Fighter1.h"
#include "DxLib.h"
#include "SceneController.h"
#include "PauseScene.h"
#include "Input.h"
#include <memory>

namespace
{
	// attackerの攻撃がtargetに当たっているか調べて、当たっていればダメージを与える
	void CheckAttackHit(FighterBase& attacker, FighterBase& target)
	{
		float al, at, ar, ab; // 攻撃判定の四角形
		if (attacker.GetAttackBox(al, at, ar, ab) == false)
		{
			return; // 判定が出ていない
		}

		float bl, bt, br, bb; // 相手の体の四角形
		target.GetBodyBox(bl, bt, br, bb);

		// 四角形どうしが重なっているか
		if (al < br && ar > bl && at < bb && ab > bt)
		{
			target.TakeDamage(attacker.GetAttackDamage());
			attacker.SetAttackHit(); // 同じ攻撃で何回も当たらないようにする
		}
	}
}

GameScene::GameScene(SceneController& controller)
    : Scene(controller)
    , m_frameCount(0)
{
    // シーンが作られたときに、プレイヤーなどを準備する
    Init();
}

GameScene::~GameScene()
{
    End();
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

	// 1P: 左側に立つ。A/D 移動、W ジャンプ、J 弱攻撃、K 強攻撃
	m_player1->SetPosition(200.0f, true);
	m_player1->SetInputPrefix("p1_"); // キーやパッドの割り当ては Input.cpp にある

	// 2P: 右側に立つ。←/→ 移動、↑ ジャンプ、, 弱攻撃、. 強攻撃
	m_player2->SetPosition(1000.0f, false);
	m_player2->SetInputPrefix("p2_");
	m_player2->SetColor(GetColor(0, 128, 255));
}

void GameScene::End()
{
	m_player1.reset();
	m_player2.reset();
}

void GameScene::Update(Input& input)
{
    // Pキーでポーズ画面を、ゲームの上に重ねる
    if (input.IsTriggered("pause"))
    {
        m_controller.PushScene(std::make_shared<PauseScene>(m_controller));
        return;
    }

    m_frameCount++;

    if (m_player1 && m_player2)
    {
        // 相手のほうを向く
        m_player1->FaceTo(m_player2->GetX());
        m_player2->FaceTo(m_player1->GetX());

        m_player1->Update(input);
        m_player2->Update(input);

        // 攻撃が当たったか調べる
        CheckAttackHit(*m_player1, *m_player2);
        CheckAttackHit(*m_player2, *m_player1);
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

    // HPバー(確認用)
    if (m_player1)
    {
        DrawBox(50, 30, 50 + m_player1->GetHp() * 4, 50, GetColor(0, 255, 0), TRUE);
        DrawBox(50, 30, 450, 50, GetColor(255, 255, 255), FALSE);
    }
    if (m_player2)
    {
        DrawBox(1230 - m_player2->GetHp() * 4, 30, 1230, 50, GetColor(0, 255, 0), TRUE);
        DrawBox(830, 30, 1230, 50, GetColor(255, 255, 255), FALSE);
    }
}
