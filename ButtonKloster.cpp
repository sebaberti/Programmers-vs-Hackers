#include <SFML/Graphics.hpp>
#include <iostream>
#include "TowerKloster.h"
#include "Button.h"
#include "ButtonKloster.h"

ButtonKloster::ButtonKloster()
{
	_mouseHover = false;
	if (!_texture.loadFromFile("img/menuContextual/button_tower_menu_kloster.png"))
	{
		throw std::runtime_error("Error img Buttom Kloster");
	}

	_sprite.setTexture(_texture);
	_sprite.setScale(0.7f, 0.7f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_tower = new TowerKloster();
	_price = _tower->getPrice();
	setSpriteHover();
	setPriceText();
	setInfo();
}
