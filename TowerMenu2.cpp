#include <SFML/Graphics.hpp>
#include <iostream> //una vez que todo funcione, esta libreria se va
#include "Spot.h"
#include "Button.h"
#include "ButtonCashSale.h"
#include "ButtonUpgrade.h"
#include "TowerMenu2.h"

TowerMenu2::TowerMenu2()
{
	_NumberMenu = 2;
	_isVisible = false;
	if (!_texture.loadFromFile("img/menuContextual/tower_menu_circle.png")) {
		throw std::runtime_error("Error img Menu Circle");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	_sprite.setScale(0.4f, 0.4f);

	//Buttons initialization
	Button* btn = new ButtonCashSale();
	_buttons.push_back(btn);
	 btn = new ButtonUpgrade(); //aca va el boton de upgrade (que tiene img de espada)
	_buttons.push_back(btn);

	_buttons[1]->setPosition(0, -100);
	_buttons[0]->setPosition(0, 85);

	_buttons[1]->setBtnNumber(1);
	_buttons[0]->setBtnNumber(2);


}

void TowerMenu2::setCurrentTower(Tower* tw)
{
	_currentTower = tw;
}
