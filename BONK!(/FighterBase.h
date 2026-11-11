#pragma once

// すべてのファイターに共通する操作を定義する基底クラス。
class FighterBase
{
public:
    virtual ~FighterBase() = default;

    // 毎フレームの入力・移動処理。
    virtual void Update() = 0;

    // ファイターの描画処理。
    virtual void Draw() const = 0;
};
