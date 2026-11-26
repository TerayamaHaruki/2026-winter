#pragma once
#include "Shot.h"
class GameScene;
/// <summary>
/// 反射レーザー
/// </summary>
class ReflectLaserShot : public Shot
{
private:
	int life_ = 10;
	int limit_ = 5;
	float length_ = 0;
	using Update_t = void (ReflectLaserShot::*)();
	void NormalUpdate();
	void ReflectUpdate();
	Update_t update_ = &ReflectLaserShot::NormalUpdate;
	std::weak_ptr<GameScene> gameScene_;
public:
	ReflectLaserShot(int handle, const Position2& pos,const Vector2& vec,std::weak_ptr<GameScene> gs,int limit=3);
	void Update()override;
	void Draw()override;
	void OnHit(std::shared_ptr<Actor> actor)override;
	void OnHit(std::shared_ptr<Collision> coll)override;
};

