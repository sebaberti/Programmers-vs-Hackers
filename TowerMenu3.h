#pragma once
#include "Tower.h"
#include "TowerMenu.h"
class TowerMenu3 : public TowerMenu
{
private:
	Tower* _currentTower;
public:
	TowerMenu3();
	void setCurrentTower(Tower*);
};