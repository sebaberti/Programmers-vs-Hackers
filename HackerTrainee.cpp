#include "HackerTrainee.h"

HackerTrainee::HackerTrainee()
{
	if (!_texture.loadFromFile("img/hackers/trainee_sprite.png")) {
		throw std::runtime_error("Error img Hacker Trainee");
	}
	_sprite.setTexture(_texture);
	_sprite.setTextureRect({0,0,64,64});
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

	_isFreezed = false;
	_type = 4;
	_currentPosition = getPosition();
	_previousPosition = _currentPosition;

	_frame = 0;
	_life = 7;
	_velocity = { 1.3f, 1.3f };
	_goldenDrop = 5;
}


int HackerTrainee::attackUtn() 
{
	return 10;
}

void HackerTrainee::saySth()
{
	if (!_bufferHacker.loadFromFile("music/TraineeSaySth.wav")) {
		throw std::runtime_error("Error al cargar Frase Hacker Trainee");
	};
	_soundHacker.setBuffer(_bufferHacker);
	_soundHacker.setVolume(25);
	_soundHacker.play();
}
