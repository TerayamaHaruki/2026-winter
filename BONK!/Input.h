#pragma once
#include <map>
#include <string>
#include <vector>

// キー入力を「名前」で調べられるようにするクラス
// 例: input.IsTriggered("ok")  → Enterキーを押した瞬間
class Input
{
public:
	Input();

	// 毎フレームの最初に1回呼ぶ
	void Update();

	// いま押している間ずっとtrue
	bool IsPressed(const std::string& code) const;

	// 押した瞬間だけtrue(押しっぱなしではfalse)
	bool IsTriggered(const std::string& code) const;

private:
	// 名前 → その名前に使うキーの一覧
	std::map<std::string, std::vector<int>> m_table;
	// 名前 → いま押されているか
	std::map<std::string, bool> m_current;
	// 名前 → 前のフレームに押されていたか
	std::map<std::string, bool> m_last;
};
