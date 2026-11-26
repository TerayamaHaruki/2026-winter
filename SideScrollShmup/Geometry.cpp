#include "Geometry.h"
#include<cmath>//数学系関数ヘッダ
#include<cassert>//assert系が入ってるヘッダ
#include<algorithm>
#include<DxLib.h>
void Vector2::Normalize() {
	float len = std::hypot(x, y);
	if (len == 0.0f) {
		x = 0.0f;
		y = 0.0f;
		return;
	}
	assert(len != 0.0f);
	x /= len;
	y /= len;
}
Vector2 Vector2::Normalized() const
{
	float len = Length();
	if (len == 0.0f) {
		return {};
	}
	return { x / len,y / len };
}
float Vector2::Length()const {
	return std::hypot(x, y);
}

Vector2 Vector2::operator-(const Vector2& right) const
{
	return { x - right.x,
			 y - right.y };
}

Vector2 Vector2::operator-() const
{
	return { -x,-y };
}

Vector2 Vector2::operator*(float scale)const
{
	return {x*scale,y*scale};
}

Vector2 Vector2::operator/(float div)const
{
	assert(div != 0.0f);
	return {x/div,y/div};
}

void Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
}

void Vector2::operator/=(float div)
{
	assert(div != 0.0f);
	x /= div;
	y /= div;
}

Vector2 GetProjectionVector(const Vector2& vec, const Vector2& axis, bool doClamp)
{
	//rate = clamp(V・L/L²,0.0f,1.0f);
	//当たり判定のための射影割合を計算する
	auto projectionRate = Dot(vec, axis) / Dot(axis,axis);
	if (doClamp) {
		projectionRate = std::clamp(projectionRate, 0.0f, 1.0f);
	}
	return axis * projectionRate;
}

Vector2 GetReflectionVector(const Vector2& inVec, const Vector2& N)
{
	// R = I - 2N(N・I)
	return inVec - N * 2.0f * Dot(N, inVec);
}

float GetIntersectionDistance(const Position2& pos, const Vector2& vec, const Circle& c,Vector2& N)
{
	auto cvec = c.pos - pos;
	auto projVec = GetProjectionVector(cvec, vec);
	auto verticalVec = cvec - projVec;
	auto backDistance = sqrtf(c.radius * c.radius - Dot(verticalVec, verticalVec));
	auto distance = projVec.Length() - backDistance;//交点までの距離
	auto intersetionVec = vec.Normalized() * distance;//交点までのベクトル
	N= (intersetionVec - cvec).Normalized();//中心から円表面までのベクトルは必ず法線ベクトルになる
	return distance;
}

Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return {left.x+right.x,
			left.y+right.y};
}

float Dot(const Vector2& lvec, const Vector2& rvec) {
	return lvec.x * rvec.x + lvec.y * rvec.y;
}

float GetDistance(const Position2& posA, const Position2& posB)
{
	return (posB - posA).Length();
}


float DegreeToRadian(float degree)
{
	//度数法(0～360)→弧度法(0.0～2π)
	return (degree * DX_PI_F) / 180.0f;
}

void Circle::Draw(uint32_t color)
{
	DrawCircleAA(pos.x, pos.y,
		radius, 32, color,false,3.0f);
}

void Capsule::Draw(unsigned int color)
{
	DrawCircleAA(pos.x, pos.y,
		radius, 32, color, false, 3.0f);
	auto posB = pos + vec;
	DrawCircleAA(posB.x, posB.y,
		radius, 32, color, false, 3.0f);
	auto v = vec.Normalized();
	v = { -v.y,v.x };
	v *= radius;
	auto pos1 = pos + v;
	auto pos2 = posB + v;
	auto pos3 = posB - v;
	auto pos4 = pos - v;

	DrawQuadrangleAA(pos1.x, pos1.y,
		pos2.x, pos2.y,
		pos3.x, pos3.y,
		pos4.x, pos4.y,
		color, false,3.0f);
}
