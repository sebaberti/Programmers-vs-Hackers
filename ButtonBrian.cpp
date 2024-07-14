#include <SFML/Graphics.hpp>
#include <iostream>
#include "TowerBrian.h"
#include "Button.h"
#include "ButtonBrian.h"

ButtonBrian::ButtonBrian()
{
	_mouseHover = false;
	if (!_texture.loadFromFile("img/menuContextual/button_tower_menu_brian.png"))
	{
		throw std::runtime_error("Error img Buttom Brian");
	}

	_sprite.setTexture(_texture);
	_sprite.setScale(0.7f, 0.7f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_tower = new TowerBrian();
	_price = _tower->getPrice();
	setSpriteHover();
	setPriceText();
	setInfo();
}
