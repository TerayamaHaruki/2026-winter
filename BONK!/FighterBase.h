#pragma once

class FighterBase
{
public:
	FighterBase();
	virtual ~FighterBase();
	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ---------- GameSceneから使う関数 ----------
	// 操作するキーを決める(右・左・上・攻撃)
	void SetKeys(int right, int left, int up, int attack);
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
	// 攻撃中かどうか
	bool m_isAttacking;
	// 攻撃中のフレーム数
	int m_attackFrame;
	// 攻撃がヒットしたかどうか
	bool m_isHit;
	// 前のフレームにJキーが押されていたか
	bool m_prevAttackKey;
	// ガード中かどうか
	bool m_isGuarding;
	// 右向きかどうか
	bool m_isFacingRight;

	// 体の色
	int m_color;
	// 操作するキー
	int m_keyRight;
	int m_keyLeft;
	int m_keyUp;
	int m_keyAttack;

	// ---------- 攻撃 ----------
	bool m_isAttacking;     // 攻撃中かどうか
	int  m_attackFrame;     // 攻撃を始めて何フレーム目か
	bool m_attackHit;       // この攻撃がもう当たったか
	int  m_prevAttackKey;   // 前のフレームに攻撃キーが押されていたか
	int  m_attackActiveStart; // 判定が出始めるフレーム(発生)
	int  m_attackActiveEnd;   // 判定が消えるフレーム(この手前まで当たる)
	int  m_attackTotal;       // 攻撃が終わるまでのフレーム数(硬直を含む)
	int  m_attackDamage;      // ダメージ量
	float m_attackW;          // 判定の幅
	float m_attackH;          // 判定の高さ
	float m_attackOffsetY;    // 判定の高さ位置(体の上から何px下か)
};