#pragma once
#include "Tower.h"
#include "TowerMenu.h"
class TowerMenu2 : public TowerMenu
{
private:
	Tower* _currentTower;
public:
	TowerMenu2();
	void setCurrentTower(Tower*);
};