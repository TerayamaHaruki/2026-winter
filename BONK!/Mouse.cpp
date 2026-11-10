#include"Mouse.h"
#include "DxLib.h"

namespace
{
	// このファイルのみで使える変数を宣言する

	// 前のフレームのクリック状態
	bool isLastLeft = false;
	bool isLastRight = false;

	// 現在のフレームのクリック状態
	bool isLeft = false;
	bool isRight = false;

	// 現在のマウス位置
	int posX = 0;
	int posY = 0;
}

namespace Mouse
{
	void Update()
	{
		// isLeft,isRightの中には前のフレームの情報が残っているので
		// それを1フレーム前の情報として残す
		isLastLeft = isLeft;
		isLastRight = isRight;

		// 現在のフレームのクリック状態を取得
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			isLeft = true;
		}
		else
		{
			isLeft = false;
		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
		{
			isRight = true;
		}
		else
		{
			isRight = false;
		}

		GetMousePoint(&posX, &posY);
	}

	bool IsTriggerLeft()
	{
		if(!isLastLeft && isLeft)
		{
			return true;
		}
		return false;
	}

	bool IsTriggerRight()
	{
		if(!isLastRight && isRight)
		{
			return true;
		}
		return false;
	}

	bool IsPressLeft()
	{
		return isLeft;
	}

	bool IsPressRight()
	{
		return isRight;
	}

	int GetX()
	{
		return posX;
	}

	int GetY()
	{
		return posY;
	}
}