#include <SFML/Graphics.hpp>
#include "MenuAbstract.h"
#include "Menu.h"
#include "MenuInfo.h"

MenuInfo::MenuInfo(bool state)
{
	_musicPlaying = state;

	if (!_textureInfo.loadFromFile("img/info/info.png")) {
		throw std::runtime_error("Error al cargar img Banner");
	}
	_info.setSize(sf::Vector2f(960, 640));
	_info.setTexture(&_textureInfo);
	_info.setPosition(sf::Vector2f(0, 0));

	_text[0].setFont(_font);
	_text[0].setCharacterSize(25);
	_text[0].setPosition(20, 20);
	_text[0].setString("BACK");
	_text[0].setOrigin(_text[0].getGlobalBounds().getPosition().x / 2, _text[0].getGlobalBounds().height / 2);
	_text[0].setFillColor(sf::Color(255, 255, 255));
}

void MenuInfo::validateClick(int mousex, int mousey, sf::RenderWindow& window, int& view)
{
	if (getText1().getGlobalBounds().contains(mousex, mousey)) {
		MenuAbstract::getInstance().setNumberMenu(1);
	}
}

void MenuInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_info, states);
	target.draw(_text[0], states);
}
