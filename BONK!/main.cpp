#include "DxLib.h"
#include "Game.h"
#include <memory>

#include "Mouse.h"
#include "Input.h"
#include "SceneController.h"
#include "TitleScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windowモードで起動する
	ChangeWindowMode(1);

	// ウィンドウサイズを16:9に
	SetGraphMode( Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	// ウィンドウのタイトル表示を変更
	SetMainWindowText("BONK!");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 入力とシーン管理を用意する
	Input input;
	SceneController controller;

	// 最初のシーンはタイトル画面
	controller.ChangeScene(std::make_shared<TitleScene>(controller));

	while (ProcessMessage() == 0)
	{
		// 現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		// 入力を更新(毎フレームの最初に1回)
		input.Update();

		// 画面をクリア
		ClearDrawScreen();


		// ゲームを処理
		Mouse::Update();
		controller.Update(input); // いまのシーンを更新
		controller.Draw();        // シーンを描画

		// 画面の書き換えを待つ
		ScreenFlip();

		// escキーを押したらゲームを強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// 画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 時間経過まで何もせずに待つ
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}