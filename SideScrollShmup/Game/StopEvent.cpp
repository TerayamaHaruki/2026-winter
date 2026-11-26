#include "StopEvent.h"
#include"../Scene/GameScene.h"
#include"EventController.h"

StopEvent::StopEvent(const Position2& pos, std::weak_ptr<GameScene> gs, std::shared_ptr<EventController> ec) :
	EventActor(pos, gs, ec)
{
	eventType_ = EventType::stop;
	if (gs.expired()) {
		return;
	}
	gs.lock()->PauseScroll();
}

void StopEvent::Update()
{
	if (eventController_->IsFinishedEvents()) {
		if (!gameScene_.expired()) {
			gameScene_.lock()->ResumeScroll();
		}
	}
}
