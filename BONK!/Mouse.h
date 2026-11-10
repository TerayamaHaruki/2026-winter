#pragma once

namespace Mouse
{
	// 毎フレームの更新処理
	// 1フレームに1回だけ呼び出す!
	void Update();

	// 左クリックが押された瞬間
	bool IsTriggerLeft();
	// 右クリックが押された瞬間
	bool IsTriggerRight();

	// 左クリックが押されているか
	bool IsPressLeft();
	// 右クリックが押されているか
	bool IsPressRight();

	// 座標の取得
	int GetX();
	int GetY();
}