#pragma once
#include "Tower.h"
class TowerBrian : public Tower
{
public:
	TowerBrian();
	Tower* clone() const override;
	void sayHi() override;
	void sayBye() override;
	void upgrade() override;
};

