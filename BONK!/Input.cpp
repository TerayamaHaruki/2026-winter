#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// 名前とキーの対応表。ここを変えれば、キー配置を変えられる
	m_table["ok"] = { KEY_INPUT_RETURN, KEY_INPUT_NUMPADENTER };
	m_table["pause"] = { KEY_INPUT_P };
	m_table["up"] = { KEY_INPUT_UP, KEY_INPUT_W };
	m_table["down"] = { KEY_INPUT_DOWN, KEY_INPUT_S };

	// 最初は全部「押していない」にしておく
	for (const auto& row : m_table)
	{
		m_current[row.first] = false;
		m_last[row.first] = false;
	}
}

void Input::Update()
{
	// 前のフレームの状態を保存してから、今の状態を調べる
	m_last = m_current;

	for (const auto& row : m_table)
	{
		bool pushed = false;
		for (int key : row.second)
		{
			if (CheckHitKey(key) == 1)
			{
				pushed = true;
			}
		}
		m_current[row.first] = pushed;
	}
}

bool Input::IsPressed(const std::string& code) const
{
	auto it = m_current.find(code);
	if (it == m_current.end())
	{
		return false; // 登録されていない名前
	}
	return it->second;
}

bool Input::IsTriggered(const std::string& code) const
{
	auto nowIt = m_current.find(code);
	auto lastIt = m_last.find(code);
	if (nowIt == m_current.end() || lastIt == m_last.end())
	{
		return false;
	}
	// 「前は押していない、今は押している」の瞬間だけtrue
	return nowIt->second == true && lastIt->second == false;
}
