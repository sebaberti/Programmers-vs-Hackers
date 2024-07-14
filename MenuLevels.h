#pragma once
#include "Menu.h"

class MenuLevels : public Menu
{
public:
	MenuLevels(bool);

	void validateClick(int, int, sf::RenderWindow&, int&) override;
	void draw(sf::RenderTarget&, sf::RenderStates) const;
};