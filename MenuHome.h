#pragma once
#include "Menu.h"

class MenuHome : public Menu
{
public:
	MenuHome(bool state);
	void validateClick(int, int, sf::RenderWindow&, int&) override;
	bool getMusicPlaying() const;
	
	void setSoundText(bool);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	
};