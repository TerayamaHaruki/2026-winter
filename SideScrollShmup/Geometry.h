#pragma once
//２変数ベクトルを表す構造体
struct Vector2 {

	Vector2():x(0.0f),y(0.0f) {}
	Vector2(float inx,float iny) :x(inx), y(iny) {}

	float x, y;
	/// <summary>
	/// 現在のベクトルを正規化(大きさを１に)する
	/// </summary>
	void Normalize();

	Vector2 Normalized()const;

	/// <summary>
	/// ベクトルの大きさを返す
	/// </summary>
	/// <returns>ベクトルの大きさ</returns>
	float Length()const;

	//右辺値がある-演算と(ただの引き算)
	Vector2 operator-(const Vector2& right)const;

	//右辺値がない-演算(ベクトルをマイナス化する)
	Vector2 operator-()const;

	//ベクトルをn倍する(ベクトルのスケーリング)
	Vector2 operator*(float scale)const;
	//ベクトルを割り算する
	Vector2 operator/(float div)const;
	
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(float scale);
	void operator/=(float div);

};
//座標を示す名前をつける。Vector2の別名を宣言しておく
using Position2 = Vector2;


/// <summary>
/// 内積を求める
/// </summary>
/// <param name="lvec">左辺値ベクトル</param>
/// <param name="rvec">右辺値ベクトル</param>
/// <returns>内積の結果</returns>
float Dot(const Vector2& lvec, const Vector2& rvec);

float GetDistance(const Position2& posA, const Position2& posB);

/// <summary>
/// 射影ベクトルを返す
/// </summary>
/// <param name="vec">ベクトル</param>
/// <param name="axis">射影される側のベクトル</param>
/// <param name="doClamp">0～1にクランプするか</param>
/// <returns>射影ベクトル</returns>
Vector2 GetProjectionVector(const Vector2& vec, const Vector2& axis, bool doClamp = false);

/// <summary>
/// 反射ベクトルを返す
/// </summary>
/// <param name="inVec">入射ベクトル</param>
/// <param name="N">法線ベクトル(正規化済み)</param>
/// <returns>反射ベクトル</returns>
Vector2 GetReflectionVector(const Vector2& inVec, const Vector2& N);
struct Circle;//プロトタイプ宣言
/// <summary>
/// 線分と円の交点までの距離を返す
/// </summary>
/// <param name="pos">線分の開始点</param>
/// <param name="vec">線分のベクトル</param>
/// <param name="c">円</param>
/// <param name="N">交点における法線の参照</param>
/// <returns>交点までの距離</returns>
float GetIntersectionDistance(const Position2& pos, const Vector2& vec, const Circle& c,Vector2& N);


//説明用に、敢えて非メンバ関数として作っています
Vector2 operator+(const Vector2& left, const Vector2& right);



//いろんなもののサイズに使用(縦と横のみ)
struct Size {
	int w;
	int h;
};
//度数法を弧度法に変換
float DegreeToRadian(float degree);

//円の構造体
struct Circle {
	Position2 pos = {};//中心座標
	float radius=0.0f;//半径
	void Draw(unsigned int color);//デバッグ用

	Circle() = default;
};

//カプセル形状の構造体
struct Capsule
{
	Position2 pos;//起点座標
	Vector2 vec;//もう一つの端点へのベクトル
	float radius;
	void Draw(unsigned int color);//デバッグ用
};

//矩形(長方形)構造体
struct Rect {

};
