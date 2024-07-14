#include <SFML/Graphics.hpp>

#include "SoundManager.h"

#include "UI.h"
UI::UI() {
	if (!_textureBgPlyInfo.loadFromFile("img/complementarias/player_info_background.png")) {
		throw std::runtime_error("Error al cargar Background Points");
	}
	_bgPlyInfo.setTexture(_textureBgPlyInfo);
	_bgPlyInfo.setPosition(420, 25);
	_bgPlyInfo.setScale(0.5, 0.5);
	_bgPlyInfo.setOrigin(_bgPlyInfo.getGlobalBounds().width / 2, _bgPlyInfo.getGlobalBounds().height / 2);

	if (!_textureCoins.loadFromFile("img/complementarias/oro.png")) {
		throw std::runtime_error("Error al cargar img Oro");
	}

	_coin.setTexture(_textureCoins);
	_coin.setPosition(460, 30);
	_coin.setScale(0.8f, 0.8f);
	_coin.setOrigin(_coin.getGlobalBounds().width / 2, _coin.getGlobalBounds().height / 2);

	if (!_textureRay.loadFromFile("img/complementarias/energia.png")) {
		throw std::runtime_error("Error al cargar img Rayo");
	}
	_ray.setTexture(_textureRay);
	_ray.setPosition(350, 30);
	_ray.setScale(0.7f, 0.7f);
	_ray.setOrigin(_ray.getGlobalBounds().width / 2, _ray.getGlobalBounds().height / 2);

	if (!_textureSkull.loadFromFile("img/complementarias/skull.png")) {
		throw std::runtime_error("Error al cargar Calavera");
	}
	_skull.setTexture(_textureSkull);
	_skull.setPosition(580, 30);
	_skull.setScale(0.5, 0.5);
	_skull.setOrigin(_skull.getGlobalBounds().width / 2, _skull.getGlobalBounds().height / 2);


	//parlante

	if (SoundManager::getInstance().getMusicOn())
	{
		if (!_textureSpeaker.loadFromFile("img/complementarias/musicOn.png"))
		{
			throw std::runtime_error("Error al cargar img mute");
		}
	}
	else
	{
		if (!_textureSpeaker.loadFromFile("img/complementarias/mute.png"))
		{
			throw std::runtime_error("Error al cargar img mute");
		}
	}

	_speaker.setSize(sf::Vector2f(80, 80));
	_speaker.setTexture(&_textureSpeaker);
	_speaker.setPosition(sf::Vector2f(900, 550));
	_speaker.setOrigin(_speaker.getGlobalBounds().width / 2, _speaker.getGlobalBounds().height / 2);

	if (!_font.loadFromFile("fuentes/fuenteMenu.ttf")) {
		throw std::runtime_error("Error al cargar la fuente del Menu \n");
	}
	for (int i = 0; i < 5; i++) {
		_text[i].setFont(_font);
		_text[i].setCharacterSize(23);
		int posX, posY;
		std::string texto;
		switch (i)
		{
		case 0:
			posX = 480;
			posY = 20;
			break;
		case 1:
			posX = 370;
			posY = 20;
			break;
		case 2:
			posX = 615;
			posY = 20;
			break;
		case 3:
			posX = 630;
			posY = 20;
			break;
		case 4:
			posX = 800;
			posY = 600;
			texto = "Home";
			break;
		default:
			break;
		}
		_text[i].setPosition(posX, posY);
		_text[i].setString(texto);
		_text[i].setFillColor(sf::Color(255, 255, 255));
	}
}

sf::RectangleShape UI::getSpeaker() const { return _speaker; }

sf::Text UI::getText5() const { return _text[4]; }

void UI::setText(int i, std::string text)
{
	_text[i].setString(text);
}

sf::Texture UI::getTextureSpeaker() const { return _textureSpeaker; }

void UI::setTextureSpeaker(std::string path) {
	if (!_textureSpeaker.loadFromFile(path)) {
		throw std::runtime_error("Error al cargar img mute");
	};
	_speaker.setTexture(&_textureSpeaker);
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_bgPlyInfo, states);
	target.draw(_ray, states);
	target.draw(_coin, states);
	target.draw(_skull, states);
	target.draw(_speaker, states);
	for (int i = 0; i < 5; i++) {
		target.draw(_text[i], states);
	}
}