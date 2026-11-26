#pragma once
#include "EventActor.h"
/// <summary>
/// スクロールを停止させるイベント
/// </summary>
class StopEvent :
    public EventActor
{
public:
    StopEvent(const Position2& pos, std::weak_ptr<GameScene> gs, std::shared_ptr<EventController> ec);
    void Update()override;
};

