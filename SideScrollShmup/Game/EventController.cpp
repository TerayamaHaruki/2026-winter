#include "EventController.h"
#include"StopEvent.h"
#include<algorithm>

EventController::EventController(std::weak_ptr<GameScene> gs, std::shared_ptr<EnemyFactory> ef):
	gameScene_(gs),
	enemyFactory_(ef)
{

}

void EventController::Create(const Position2& pos, EventType type)
{
	if (type == EventType::stop) {
		events_.push_back(std::make_shared<StopEvent>(pos,gameScene_,shared_from_this()));
	}
}

void EventController::Update()
{
	for (auto& event : events_) {
		event->Update();
	}
	std::erase_if(events_, [](const std::shared_ptr<EventActor>& event) {
		return event->IsDead();
		});
}

bool EventController::IsFinishedEvents() const
{
	auto count = std::count_if(events_.begin(), events_.end(),
		[](const std::shared_ptr<EventActor>& event) {
			return event->GetEventType() != EventType::stop &&
				event->IsFinished();
		});
	return (count == events_.size() - 1);
}

void EventController::ActivateEvents()
{
	for (auto& event : events_) {
		event->Activate();
	}
}
