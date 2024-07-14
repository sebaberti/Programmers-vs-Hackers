#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level4.h"
#include "Level5.h"
#include "Manager.h"

Manager* Manager::_currentInstance = nullptr;

Manager& Manager::getInstance()
{
	if (Manager::_currentInstance == nullptr)
	{
		Manager::_currentInstance = new Manager(); //el Manager nace con nivel=1
	}
	return *Manager::_currentInstance;
}



Manager::Manager(int level): _currentLevel(nullptr)
{
	setNumberLevel(level);
}

Level* Manager::getLevel() const { return _currentLevel; }

void Manager::setLevel(Level& level)
{
	_currentLevel = &level;
}

void Manager::setNumberLevel(int IdLevel) {
	switch (IdLevel)
	{
	case 0:
		 _currentLevel = new Level1();
		break;
	case 1:
		_currentLevel = new Level2();
		break;
	case 2:
		_currentLevel = new Level3();
		break;
	case 3:
		_currentLevel = new Level4();
		break;
	case 4:
		_currentLevel = new Level5();
		break;
	default:
		break;
	}
}

void Manager::validateClick(int mousex, int mousey, sf::RenderWindow& window, int& view) {
	_currentLevel->validateClick(mousex, mousey, view);
}

void Manager::mouseCheck(sf::Vector2i& mousePosition)
{
	_currentLevel->mouseCheck(mousePosition);
}

void Manager::update(sf::Vector2i& mousePosition, int& view)
{
	_currentLevel->update(mousePosition, view);
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_currentLevel, states);
}

Manager::~Manager()
{
	//delete _currentLevel;
}
