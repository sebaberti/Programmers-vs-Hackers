#include "HackerJunior.h"


HackerJunior::HackerJunior()
{
	if (!_texture.loadFromFile("img/hackers/junior_sprite.png")) {
		throw std::runtime_error("Error img Hacker Junior");
	}
	_sprite.setTexture(_texture);
	_sprite.setTextureRect({ 0,0,64,64 });
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

	_isFreezed = false;
	_type = 2;
	_currentPosition = getPosition();
	_previousPosition = _currentPosition;
	_frame = 0;
	_life = 15;
	_velocity = { 1.1f, 1.1f };
	_goldenDrop = 15;

}


int HackerJunior::attackUtn() {
	
	return 20;
}

void HackerJunior::saySth()
{
	if (!_bufferHacker.loadFromFile("music/JuniorSaySth.wav")) {
		throw std::runtime_error("Error al cargar Frase Hacker Junior");
	};
	_soundHacker.setBuffer(_bufferHacker);
	_soundHacker.setVolume(25);
	_soundHacker.play();
}
