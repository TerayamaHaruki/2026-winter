#include "ReflectLaserShot.h"
#include<DxLib.h>
#include"../Scene/GameScene.h"
#include"ShotFactory.h"
constexpr float grow_per_frame = 8.0f;
constexpr float hit_radius = 3.0f;
constexpr float max_length = 100.0f;
constexpr float shot_speed = 8.0f;
void ReflectLaserShot::NormalUpdate()
{
	auto& pos = GetPosition();
	pos += vel_;
	length_ = std::min(length_ + grow_per_frame, max_length);
	coll_->SetCapsule(pos, -vel_.Normalized() * length_, hit_radius);
	if (IsOutScreen(pos)) {
		isDead_ = true;
	}
}
void ReflectLaserShot::ReflectUpdate()
{
	auto& pos = GetPosition();
	length_ = std::max(length_ - grow_per_frame, 0.0f);
	coll_->SetCapsule(pos, -vel_.Normalized() * length_, hit_radius);
	if (length_ == 0.0f) {
		isDead_ = true;
	}
}
ReflectLaserShot::ReflectLaserShot(int handle, const Position2& pos, const Vector2& vec,std::weak_ptr<GameScene> gs,int limit):
	Shot(handle,pos,hit_radius),
	gameScene_(gs),
	limit_(limit)
{
	coll_->SetCapsule(pos, -vec * length_, hit_radius);
	vel_ = vec * shot_speed;
}

void ReflectLaserShot::Update()
{
	(this->*update_)();
}

void ReflectLaserShot::Draw()
{
	auto& cap = GetCollision()->GetCapsule();
	const auto& posA = cap.pos;
	const auto posB = posA + cap.vec;
	DrawLineAA(posA.x, posA.y, posB.x, posB.y, 0x88ff88, hit_radius);
}

void ReflectLaserShot::OnHit(std::shared_ptr<Actor> actor)
{
	if (!actor) {
		return;
	}
	if (actor->GetActorType() == ActorType::enemy) {
		--life_;
	}
	if (life_ < 0) {
		isDead_=true;
	}
}
void 
ReflectLaserShot::OnHit(std::shared_ptr<Collision> coll) {
	if (update_ == &ReflectLaserShot::ReflectUpdate) {
		return;
	}
	if (!coll) {
		return;
	}
	if (coll->GetType() == CollisionType::circle) {
		auto& pos = GetPosition();//レーザーの終点
		//反射した瞬間に衝突判定が発生しないように、円から遠ざかる方向の速度の場合は反応しない
		auto toCenter = coll->GetCircle().pos - pos;//中心に向かうベクトル
		if (Dot(toCenter, vel_) <= 0.0f) {
			return;
		}

		auto& capsule = GetCollision()->GetCapsule();
		auto lineStart = pos + capsule.vec;//レーザーの始点
		auto lineVec = -capsule.vec;
		auto& circle = coll->GetCircle();
		Vector2 N = {};
		float distance = GetIntersectionDistance(lineStart, lineVec, circle,N);
		pos = lineStart + lineVec.Normalized() * distance;
		auto vec = -vel_.Normalized() * (lineVec.Length() - distance);
		capsule.pos = pos;
		capsule.vec = vec;

		//当たった円の法線ベクトルを求める
		update_ = &ReflectLaserShot::ReflectUpdate;
		if (limit_ <= 0) {
			return;
		}
		if (!gameScene_.expired()) {
			auto& shotFactory = gameScene_.lock()->GetShotFactory();
			auto refVec = GetReflectionVector(lineVec, N).Normalized();
			shotFactory->Fire(pos, ShotType::re_reflect_laser, refVec,limit_-1);
		}

	}
}