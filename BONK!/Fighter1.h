#pragma once

#include "FighterBase.h"

class Fighter1 : public FighterBase
{
public:
	Fighter1();
	virtual ~Fighter1();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

};