#pragma once
#include <cmath>

class Vec2
{
public:
	float x;
	float y;

public:
	// 引数なしコンストラクタ　各成分を0で初期化
	Vec2() : Vec2(0.0f,0.0f) {}
	// 実態生成時に同時に初期化も可能
	Vec2(float x_, float y_):
		x(x_),
		y(y_)
	{ }

	// ベクトルの長さの2乗を取得する
	float sqLength() const
	{
		return (x * x) + (y * y);
	}

	// ベクトルの長さを取得する
	float Length() const
	{
		return sqrtf(sqLength());
	}

	// 自身の正規化を行う
	void Normalize()
	{
		float len = Length();
		// ゼロ徐算回避
		if (len == 0.0f)	return;
		x /= len;
		y /= len;
	}
};