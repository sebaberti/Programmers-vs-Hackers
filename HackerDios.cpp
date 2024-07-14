#include "HackerDios.h"

HackerDios::HackerDios()
{
	if (!_texture.loadFromFile("img/hackers/god_sprite.png")) {
		throw std::runtime_error("Error img Hacker Dios");
	}

	_sprite.setTexture(_texture);

	//region de la textura que se muestra inicialmente
	_sprite.setTextureRect({ 0,0,64,64 });
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

	_isFreezed = false;

	_type = 1;
	_currentPosition = getPosition();
	_previousPosition = _currentPosition;
	_frame = 0;
	_life = 50;
	_velocity = { 0.8f,0.8f };
	_goldenDrop = 70;
}

int HackerDios::attackUtn() {

	return 70;
}

void HackerDios::saySth()
{
	if (!_bufferHacker.loadFromFile("music/DiosSaySth.wav")) {
		throw std::runtime_error("Error al cargar Frase Hacker Dios");
	};

	_soundHacker.setBuffer(_bufferHacker);
	_soundHacker.setVolume(25);
	_soundHacker.play();
}
