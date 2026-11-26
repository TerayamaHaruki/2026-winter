#pragma once

#include <string>

class Input;

class FighterBase
{
public:
	FighterBase();
	virtual ~FighterBase();
	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update(Input& input) = 0;
	virtual void Draw() = 0;

	// GameSceneから使う関数
	// 操作する入力の名前の頭を決める("p1_" か "p2_")
	// 例: "p1_" なら "p1_right" や "p1_weak" をInputで調べる
	void SetInputPrefix(const std::string& prefix);
	// 開始位置と向きを決める
	void SetPosition(float x, bool isFacingRight);
	// 体の色を決める
	void SetColor(int color);
	// 相手のほうを向く(地上で攻撃していないときだけ)
	void FaceTo(float targetX);
	// X座標とHPを調べる
	float GetX() const;
	int GetHp() const;
	// ダメージを受ける
	void TakeDamage(int damage);
	// 体の当たり判定の四角形を調べる
	void GetBodyBox(float& left, float& top, float& right, float& bottom) const;
	// 攻撃の当たり判定を調べる(判定が出ていないときはfalse)
	bool GetAttackBox(float& left, float& top, float& right, float& bottom) const;
	// 攻撃のダメージ量
	int GetAttackDamage() const;
	// 攻撃が当たったことを覚える(同じ攻撃で何回もダメージが入らないように)
	void SetAttackHit();

protected:
	// 攻撃判定が出ている時間かどうか
	bool IsAttackActive() const;
	// 攻撃判定の四角形を計算する
	void CalcAttackBox(float& left, float& top, float& right, float& bottom) const;

	int hp;
	// 座標
	float m_x;
	float m_y;
	// 重力
	float m_gravity;
	// 縦方向の速度(上向きがマイナス)
	float m_vy;
	// サイズ
	float m_width;
	float m_height;
	// 移動速度
	float m_ForwardSpeed;
	float m_BackSpeed;
	// ジャンプ力
	float m_Jump;
	// ジャンプ中の横方向(1:前 0:垂直 -1:後ろ)
	int m_jumpDir;
	// 空中にいるかどうか
	bool m_air;
	// ガード中かどうか
	bool m_isGuarding;
	// 右向きかどうか
	bool m_isFacingRight;

	// 体の色
	int m_color;
	// 入力の名前の頭("p1_" か "p2_")
	std::string m_prefix;
	bool m_isCrouching;

	// 攻撃
	bool m_isAttacking;     // 攻撃中かどうか
	int  m_attackFrame;     // 攻撃を始めて何フレーム目か
	bool m_attackHit;       // この攻撃がもう当たったか
	bool m_isStrongAttack;  // 今の攻撃が強攻撃かどうか
	int  m_attackActiveStart; // 判定が出始めるフレーム(発生)
	int  m_attackActiveEnd;   // 判定が消えるフレーム(この手前まで当たる)
	int  m_attackTotal;       // 攻撃が終わるまでのフレーム数(硬直を含む)
	int  m_attackDamage;      // ダメージ量
	float m_attackW;          // 判定の幅
	float m_attackH;          // 判定の高さ
	float m_attackOffsetY;    // 判定の高さ位置(体の上から何px下か)
};