#pragma once
#include <iostream>
#include "Level.h"
#include "MenuAbstract.h"

class Manager : public sf::Drawable
{
private:
	Manager(int level =0 ); //Singleton
	static Manager* _currentInstance; //Singleton
	Level *_currentLevel;

public:
	static Manager& getInstance(); //Singleton
	Level* getLevel() const;
	void setLevel(Level&);
	void setNumberLevel(int);
	void validateClick(int, int, sf::RenderWindow&, int&);
	void mouseCheck(sf::Vector2i&);
	void update(sf::Vector2i&, int& view);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	~Manager();
};

