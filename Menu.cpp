#include "Menu.h"

Menu::Menu()
	: _soundManager(SoundManager::getInstance())
{
	//fondo
	if (!_textureBanner.loadFromFile("img/banner/imgPortada.png")) {
		throw std::runtime_error("Error al cargar img Banner");
	}
	_banner.setSize(sf::Vector2f(1024, 768));
	_banner.setTexture(&_textureBanner);
	_banner.setPosition(sf::Vector2f(0, 0));

	//texto
	if (!_font.loadFromFile("fuentes/fuenteMenu.ttf")) {
		throw std::runtime_error("Error al cargar la fuente del Menu \n");
	}
}

void Menu::mouseCheck(sf::Vector2i& mousePosition)
{
	//verificamos si el mouse esta dentro de los limites globales del texto
	//para cambiar el color(HOVER)
	for (int i = 0; i <6; i++) {
		if (_text[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))){
			_text[i].setFillColor(sf::Color(0, 50, 255));
		}
		else {
			_text[i].setFillColor(sf::Color(255, 255, 255));
		}
	}
}

sf::Text Menu::getText1() const { return _text[0]; }
sf::Text Menu::getText2() const { return _text[1]; }
sf::Text Menu::getText3() const { return _text[2]; }
sf::Text Menu::getText4() const { return _text[3]; }
sf::Text Menu::getText5() const { return _text[4]; }
sf::Text Menu::getText6() const { return _text[5]; }

void Menu::setMusicPlaying(bool playing) { _musicPlaying = playing; }


void Menu::setSound(bool play)
{
	if (_soundManager.getMusicOn())
	{
		_soundManager.playMusic();
	}
	else
	{
		_soundManager.pauseMusic();
	}
}

bool Menu::getMusicPlaying() const {
	return _musicPlaying;
}

float Menu::getSoundPosition() const {
	return _sound.getPlayingOffset().asSeconds();
}


//establece la posición de reproducción del sonido _sound al
//tiempo especificado por sf::seconds(position).
void Menu::setSoundPosition(float position) {
	_sound.setPlayingOffset(sf::seconds(position));
}

void Menu::update(sf::Vector2i& mousePosition)
{
	mouseCheck(mousePosition);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(_banner, states);
}

Menu::~Menu()
{
	/*_sound.stop();
	_sound.resetBuffer();*/
}
