#include <SFML/Graphics.hpp>
#include <iostream> //una vez que todo funcione, esta libreria se va
#include "Spot.h"
#include "Button.h"
#include "ButtonBrian.h"
#include "ButtonKloster.h"
#include "ButtonMaxiSar.h"
#include "ButtonMaxiWenner.h"
#include "TowerMenu1.h"


TowerMenu1::TowerMenu1()
{
	_NumberMenu = 1;
	_isVisible = false;
	if (!_texture.loadFromFile("img/menuContextual/tower_menu_circle.png")) {
		throw std::runtime_error("Error img Menu Circle");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	_sprite.setScale(0.4f, 0.4f);

	Button* btn = new ButtonBrian(); //saque este formato de los spots.. pero necesito q cada boton sea distinto
	_buttons.push_back(btn);
	btn = new ButtonMaxiSar();
	_buttons.push_back(btn);
	btn = new ButtonMaxiWenner();
	_buttons.push_back(btn);
	btn = new ButtonKloster();
	_buttons.push_back(btn);

	_buttons[0]->setPosition(0, -100);
	_buttons[1]->setPosition(85, 0);
	_buttons[2]->setPosition(0, 85);
	_buttons[3]->setPosition(-100, 0);

	int i = 0;
	for (Button* button : _buttons) {
		button->setBtnNumber(i);
		//button->setPriceText();
		i++;
	}

	
}