#include <SFML/Graphics.hpp>
#include <iostream> //una vez que todo funcione, esta libreria se va
#include "Spot.h"
#include "Button.h"
#include "ButtonCashSale.h"
#include "TowerMenu3.h"

TowerMenu3::TowerMenu3()
{
	_NumberMenu = 3;
	_isVisible = false;
	if (!_texture.loadFromFile("img/menuContextual/tower_menu_circle.png")) {
		throw std::runtime_error("Error img Menu Circle");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	_sprite.setScale(0.4f, 0.4f);

	//Buttons initialization
	Button* btn = new ButtonCashSale();  //con esta linea se rompe
	_buttons.push_back(btn);

	_buttons[0]->setPosition(0, 85);
	_buttons[0]->setBtnNumber(2);

	
}

void TowerMenu3::setCurrentTower(Tower* tw)
{
	_currentTower = tw;
}
