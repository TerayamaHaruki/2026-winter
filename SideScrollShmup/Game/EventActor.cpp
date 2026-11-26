#include "EventActor.h"

EventActor::EventActor(const Position2& pos,std::weak_ptr<GameScene> gs, std::shared_ptr<EventController> ec):
    gameScene_(gs),
    eventController_(ec),
    Actor(pos,0.0f)
{
}

bool EventActor::IsActivated() const
{
    return isActivated_;
}

bool EventActor::IsFinished() const
{
    return isFinished_;
}
EventType 
EventActor::GetEventType()const {
    return eventType_;
}

void EventActor::Activate()
{
    isActivated_ = true;
}
