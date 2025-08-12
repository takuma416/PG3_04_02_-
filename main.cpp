#include <Novice.h>
#include "GameManager.h"
#include "ImGuiManager.h"

const char kWindowTitle[] = "GC1D_04_オガワタクマ_タイトル";

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // GameManager を1回だけ生成
    GameManager* gameManager = new GameManager();

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // ImGui フレーム開始
        ImGuiManager::GetInstance()->Begin();

        // ゲーム更新・描画
        gameManager->Update(keys, preKeys);
        gameManager->Draw();

        // ImGui フレーム終了＆描画
        ImGuiManager::GetInstance()->End();
        ImGuiManager::GetInstance()->Draw();

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // GameManager を解放
    delete gameManager;

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}

