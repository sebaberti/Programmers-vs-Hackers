#include "Manager.h"
#include "FileLevel.h"
#include "MenuAbstract.h"
#include "MenuLevels.h"

MenuLevels::MenuLevels(bool state) //state no se usa?
{
	FileLevels arc;
	Levels reg;
	
	//texto
	for (int i = 0; i < 6; i++) {
		_text[i].setFont(_font);
		_text[i].setCharacterSize(30);
		int posY, posX=250;
		std::string texto;

		switch (i)
		{
		case 0:
			posY = 100;
			break;
		case 1:
			posY = 200;
			break;
		case 2:
			posY = 300;
			break;
		case 3:
			posY = 400;
			break;
		case 4:
			posY = 500;
			break;
		case 5:
			posX = 25;
			posY = 25;
			texto = "BACK";
			break;
		}
		if (i != 5) {
			reg = arc.read(i);
			//si es verdadero asigna el nombre del nivel que contiene el archivo
			if (reg.getStatus()) {
				texto = reg.getName();
			}
			else {
				texto = "";
			}
		}		
		_text[i].setPosition(posX, posY);
		_text[i].setString(texto);
		_text[i].setOrigin(_text[i].getGlobalBounds().getPosition().x / 2, _text[i].getGlobalBounds().height / 2);
		_text[i].setFillColor(sf::Color(255, 255, 255));
	}
}


//validamos clicks para ver a que nivel entramos
void MenuLevels::validateClick(int mousex, int mousey, sf::RenderWindow& window, int& view)
{
	if (getText1().getGlobalBounds().contains(mousex, mousey)) {
		Manager::getInstance().setNumberLevel(0);
		view = 2;
	}
	else if (getText2().getGlobalBounds().contains(mousex, mousey) && getText2().getString()!="") {
		Manager::getInstance().setNumberLevel(1);
		view = 2;
	}
	else if (getText3().getGlobalBounds().contains(mousex, mousey) && getText2().getString() != "") {
		Manager::getInstance().setNumberLevel(2);
		view = 2;
	}
	else if (getText4().getGlobalBounds().contains(mousex, mousey) && getText2().getString() != "") {
		Manager::getInstance().setNumberLevel(3);
		view = 2;
	}
	else if (getText5().getGlobalBounds().contains(mousex, mousey) && getText2().getString() != "") {
		Manager::getInstance().setNumberLevel(4);
		view = 2;
	}
	//VOLVER:
	else if (getText6().getGlobalBounds().contains(mousex, mousey)) {
		MenuAbstract::getInstance().setNumberMenu(1);
	}
}

void MenuLevels::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	Menu::draw(target, states);
	for (int i = 0; i < 6; i++) {
		target.draw(_text[i], states);
	}
}