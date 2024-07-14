#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "ButtonCashSale.h"

ButtonCashSale::ButtonCashSale()
{
	_mouseHover = false;
	if (!_texture.loadFromFile("img/menuContextual/button_tower_updateMenu_sell.png"))
	{
		throw std::runtime_error("Error img Buttom CashSale");
	}

	_sprite.setTexture(_texture);
	_sprite.setScale(0.7f, 0.7f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	setSpriteHover();
}


