#pragma once
#include "Actor.h"
class Player;
class GameScene;
//フォース(プレイヤーの前方もしくは後方でガードする)
class Force : public Actor
{
	int handle_;
	std::weak_ptr<Player> player_;
	std::weak_ptr<GameScene> gameScene_;
	bool isBack_ = false;
	int frame_ = 0;
	Vector2 vel_ = {};
	Position2 kickStartPos_ = {};
	Vector2 attachedForceOffset_ = {};
	using Update_t = void (Force::*)();
	// くっついてる状態
	void AttachedUpdate();

	// 完全に離れてる状態
	void SeparatedUpdate();

	// 近くに寄りつつある状態
	void ComingUpdate();

	// 遠くに吹っ飛ばされてる状態
	void KickingUpdate();

	Update_t update_ = &Force::SeparatedUpdate;
	/// 離す
	void Kick();
	/// 寄せる
	void ComeHere();
	//くっつく(自分からくっついていったときに呼ばれる)
	void AttachForce();
public:
	Force(int handle,std::weak_ptr<Player> player, std::weak_ptr<GameScene> gs);
	void Update()override;
	void Draw()override;
	void OnHit(const std::shared_ptr<Actor> actor)override;
	void Run();
	//離れるか、くっつくかのアクションを起こす
	void Action();
	
	bool IsBackAttached()const;//フォースが後ろにくっついているか

};

