#pragma once
#include "Actor.h"
#include<memory>

enum class EventType {
	none,
	stop,
	volcano,
	robo,
	boss
};

class EventController;
class GameScene;
/// <summary>
/// イベントの基底クラス
/// </summary>
class EventActor : public Actor
{
protected:
	std::weak_ptr<GameScene> gameScene_;
	std::shared_ptr<EventController> eventController_;
	bool isActivated_ = true;
	bool isFinished_ = false;
	EventType eventType_;
public:
	EventActor(const Position2& pos ,std::weak_ptr<GameScene> gs, std::shared_ptr<EventController> ec);
	void Draw()override {};
	virtual void OnHit(const std::shared_ptr<Actor> actor)override {};
	EventType GetEventType()const;
	void Activate();
	/// <summary>
	/// 起動済みか
	/// </summary>
	/// <returns>true:起動済み / false:まだ起動してない</returns>
	bool IsActivated()const;
	/// <summary>
	/// イベント終了？
	/// </summary>
	/// <returns>true:イベント終了 / false:イベントはまだ続いている</returns>
	bool IsFinished()const;
};

