#include <SFML/Graphics.hpp>

#include <iostream>
#include "Menu.h"
#include "MenuHome.h"
#include "MenuLevels.h"
#include "MenuInfo.h"
#include "MenuAbstract.h"
#include "SoundManager.h"

MenuAbstract* MenuAbstract::_currentInstance = nullptr;

MenuAbstract& MenuAbstract::getInstance() {
	if (MenuAbstract::_currentInstance == nullptr) {
		MenuAbstract::_currentInstance = new MenuAbstract();
	}
	return *MenuAbstract::_currentInstance;
}


MenuAbstract::MenuAbstract(int idMenu) : _currentMenu(nullptr) {
	setNumberMenu(idMenu);
}

void MenuAbstract::setNumberMenu(int idMenu)
{
	bool state;
	SoundManager& _soundManger = SoundManager::getInstance();

	switch (idMenu)
	{
	case 1:
		if (_currentMenu != nullptr)
		{
			state = _soundManger.getMusicOn();
			_currentMenu = new MenuHome(state);
		}
		else
		{
			_currentMenu = new MenuHome(true);
			_currentMenu->setSound(true);
		}
		break;
	case 2:
	{
		state = _soundManger.getMusicOn();
		_currentMenu = new MenuLevels(state);
	}
	break;
	case 3:
	{
		state = _soundManger.getMusicOn();
		_currentMenu = new MenuInfo(state);
	}
	break;
	default:
		break;
	}
}

void MenuAbstract::validateClick(int mousex, int mousey, sf::RenderWindow& window, int& view)
{
	_currentMenu->validateClick(mousex, mousey, window, view);
}



void MenuAbstract::update(sf::Vector2i& mousePosition)
{
	_currentMenu->update(mousePosition);
}


void MenuAbstract::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(*_currentMenu, states);
}


MenuAbstract::~MenuAbstract()
{
	
	//delete _currentMenu; // Eliminar el menú actual
	//_currentMenu = nullptr;
	
}