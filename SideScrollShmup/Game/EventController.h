#pragma once
#include<list>
#include<memory>
#include"../Geometry.h"
#include"EventActor.h"

class GameScene;
class EnemyFactory;
/// <summary>
/// イベントオブジェクトを管理します
/// </summary>
class EventController : public std::enable_shared_from_this<EventController>
{
private:
	std::list<std::shared_ptr<EventActor> > events_;
	std::weak_ptr<GameScene> gameScene_;
	std::shared_ptr<EnemyFactory> enemyFactory_;
public:
	EventController(std::weak_ptr<GameScene> gs, std::shared_ptr<EnemyFactory> ef);
	void Create(const Position2& pos,EventType type);
	void Update();
	/// <summary>
	/// 停止以外のイベントが終了したか
	/// </summary>
	/// <returns>true:終了している / false:まだ続いている</returns>
	bool IsFinishedEvents()const;

	/// <summary>
	/// イベントを起動させる
	/// </summary>
	void ActivateEvents();
};

