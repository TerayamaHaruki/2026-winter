#include "Input.h"
#include "DxLib.h"

Input::Input()
{
	// タイトル・ポーズなどの操作
	m_table["ok"] = {
		{ PeripheralType::keybd, KEY_INPUT_RETURN },
		{ PeripheralType::keybd, KEY_INPUT_NUMPADENTER },
		{ PeripheralType::pad,   PAD_INPUT_A },
	};
	m_table["pause"] = {
		{ PeripheralType::keybd, KEY_INPUT_P },
	};
	m_table["up"] = {
		{ PeripheralType::keybd, KEY_INPUT_UP },
		{ PeripheralType::keybd, KEY_INPUT_W },
		{ PeripheralType::pad,   PAD_INPUT_UP },
	};
	m_table["down"] = {
		{ PeripheralType::keybd, KEY_INPUT_DOWN },
		{ PeripheralType::keybd, KEY_INPUT_S },
		{ PeripheralType::pad,   PAD_INPUT_DOWN },
	};

	// 1P
	m_table["p1_right"] = {
		{ PeripheralType::keybd, KEY_INPUT_D },
		{ PeripheralType::pad,   PAD_INPUT_RIGHT },
	};
	m_table["p1_left"] = {
		{ PeripheralType::keybd, KEY_INPUT_A },
		{ PeripheralType::pad,   PAD_INPUT_LEFT },
	};
	m_table["p1_up"] = {
		{ PeripheralType::keybd, KEY_INPUT_W },     // スペースにするならここを KEY_INPUT_SPACE に
		{ PeripheralType::pad,   PAD_INPUT_UP },
		{ PeripheralType::pad,   PAD_INPUT_A },
	};
	m_table["p1_weak"] = {
		{ PeripheralType::keybd, KEY_INPUT_J },
		{ PeripheralType::pad,   PAD_INPUT_C },     // Xボタン
	};
	m_table["p1_strong"] = {
		{ PeripheralType::keybd, KEY_INPUT_K },
		{ PeripheralType::pad,   PAD_INPUT_X },     // Yボタン
	};

	// 2P
	m_table["p2_right"] = {
		{ PeripheralType::keybd, KEY_INPUT_RIGHT },
		{ PeripheralType::pad2,  PAD_INPUT_RIGHT },
	};
	m_table["p2_left"] = {
		{ PeripheralType::keybd, KEY_INPUT_LEFT },
		{ PeripheralType::pad2,  PAD_INPUT_LEFT },
	};
	m_table["p2_up"] = {
		{ PeripheralType::keybd, KEY_INPUT_UP },
		{ PeripheralType::pad2,  PAD_INPUT_UP },
		{ PeripheralType::pad2,  PAD_INPUT_A },
	};
	m_table["p2_weak"] = {
		{ PeripheralType::keybd, KEY_INPUT_COMMA },
		{ PeripheralType::pad2,  PAD_INPUT_C },
	};
	m_table["p2_strong"] = {
		{ PeripheralType::keybd, KEY_INPUT_PERIOD },
		{ PeripheralType::pad2,  PAD_INPUT_X },
	};

	// 最初は全部「押していない」にしておく(ここは変更なし)
	for (const auto& row : m_table)
	{
		m_current[row.first] = false;
		m_last[row.first] = false;
	}
}


void Input::Update()
{
	// 前のフレームの状態を保存する(ここは変更なし)
	m_last = m_current;

	// パッドの状態を、最初に1回だけ読む
	int padState = 0;   // 1つ目のパッド
	int pad2State = 0;  // 2つ目のパッド
	int padNum = GetJoypadNum();  // つながっているパッドの数
	if (padNum > 0)
	{
		padState = GetJoypadInputState(DX_INPUT_PAD1);
	}
	if (padNum > 1)
	{
		pad2State = GetJoypadInputState(DX_INPUT_PAD2);
	}

	for (const auto& row : m_table)
	{
		bool pushed = false;

		// 登録されている入力を1つずつ調べる
		for (const InputInfo& info : row.second)
		{
			// 機器の種類によって、調べ方を変える
			switch (info.type)
			{
			case PeripheralType::keybd:
				if (CheckHitKey(info.id) == 1)
				{
					pushed = true;
				}
				break;

			case PeripheralType::pad:
				if ((padState & info.id) != 0)
				{
					pushed = true;
				}
				break;

			case PeripheralType::pad2:
				if ((pad2State & info.id) != 0)
				{
					pushed = true;
				}
				break;
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
