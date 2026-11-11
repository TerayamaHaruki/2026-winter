#include "DxLib.h"
#include "Game.h"
#include <memory>

#include "Mouse.h"
#include "SceneMain.h"
#include "SceneController.h"

// プログラムは WinMain から始まります。
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // Windowモードで起動する。
    ChangeWindowMode(1);

    // ウィンドウサイズを16:9にする。
    SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

    // ウィンドウのタイトル表示を変更する。
    SetMainWindowText("BONK!");

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    // シーンの生成・切り替え・更新・描画はSceneControllerに任せる。
    SceneController sceneController;
    sceneController.Start(std::make_unique<SceneMain>(sceneController));

    while (ProcessMessage() == 0)
    {
        const LONGLONG start = GetNowHiPerformanceCount();

        ClearDrawScreen();

        Mouse::Update();
        sceneController.Update();
        sceneController.Draw();

        ScreenFlip();

        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // 約60FPSで動かす。
        while (GetNowHiPerformanceCount() - start < 16667)
        {
        }
    }

    sceneController.End();
    DxLib_End();

    return 0;
}
