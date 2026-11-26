#include "ShotFactory.h"
#include"../Application.h"
#include"../FileLoader.h"
#include"NormalShot.h"
#include"ChargeShot.h"
#include"MissileShot.h"
#include"ReflectLaserShot.h"

ShotFactory::ShotFactory(std::weak_ptr<GameScene> gs):gameScene_(gs)
{
	auto loader = Application::GetInstance().GetLoader();
	shotImgs_.push_back(loader->LoadGraph(L"Asset/img/Actor/shot.png", AssetType::temporary));
	shotImgs_.push_back(loader->LoadGraph(L"Asset/img/Actor/charge_shot_3.png", AssetType::temporary));
	shotImgs_.push_back(loader->LoadGraph(L"Asset/img/Actor/missile_shot.png", AssetType::temporary));
	shotImgs_.push_back(-1);//レーザーの画像は今はない(3way)
	shotImgs_.push_back(-1);//レーザーの画像は今はない(再反射)

	//通常弾
	createFuncs_.push_back([](int handle, const Position2& pos,const Vector2&,int) {
		return std::make_shared<NormalShot>(handle, pos);
		});
	//チャージショット
	createFuncs_.push_back([](int handle, const Position2& pos, const Vector2&,int) {
		return std::make_shared<ChargeShot>(handle,pos);
	});
	//ミサイル弾
	createFuncs_.push_back([this](int handle, const Position2& pos, const Vector2&,int) {
		return std::make_shared<MissileShot>(handle, pos,gameScene_);
		});
	//3-way反射レーザー
	createFuncs_.push_back([](int handle, const Position2& pos, const Vector2&,int) {
		return std::shared_ptr<Shot>();
		});

	//再反射レーザー
	createFuncs_.push_back([this](int handle, const Position2& pos, const Vector2& vec,int limit) {
		return std::make_shared<ReflectLaserShot>(handle, pos, vec, gameScene_,limit);
		});


}

void ShotFactory::Update()
{
	for (auto& shot : shots_) {
		shot->Update();
	}
	std::erase_if(shots_, [](auto shot) {
		return shot->IsDead();
		});
}

void ShotFactory::Draw()
{
	for (auto& shot : shots_) {
		shot->Draw();
	}
}

void ShotFactory::Fire(const Position2& pos, ShotType shotType, const Vector2& vec,int limit)
{
	constexpr int reflect_init_limit = 3;
	int typeIndex = static_cast<int>(shotType);
	int handle = shotImgs_[typeIndex];
	if (shotType == ShotType::reflect_laser) {
		shots_.push_back(
			std::make_shared<ReflectLaserShot>(handle,pos,Vector2(vec.x,0.0f),gameScene_, reflect_init_limit)
		);
		shots_.push_back(
			std::make_shared<ReflectLaserShot>(handle, pos, Vector2(vec.x, -1.0f).Normalized(),gameScene_, reflect_init_limit)
		);
		shots_.push_back(
			std::make_shared<ReflectLaserShot>(handle, pos, Vector2(vec.x, 1.0f).Normalized(),gameScene_, reflect_init_limit)
		);
	}
	else {
		shots_.push_back(createFuncs_[typeIndex](handle, pos,vec,limit));
	}
	
}

ShotFactory::Shots_t& ShotFactory::GetShots()
{
	return shots_;
}
