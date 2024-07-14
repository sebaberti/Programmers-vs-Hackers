#include "HackerBoss.h"

HackerBoss::HackerBoss()
{
	if (!_texture.loadFromFile("img/hackers/Boss_sprite.png")) {
		throw std::runtime_error("Error img Hacker Boss");
	}
	_sprite.setTexture(_texture);
	_sprite.setTextureRect({ 0,0,124,125 });
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);

	_isFreezed = false;
	_type = 5;

	_currentPosition = getPosition();
	_previousPosition = _currentPosition;

	_frame = 0;
	_life = 100;
	_velocity = { 0.4f,0.4f };
	_goldenDrop = 900;
}

void HackerBoss::animation(float _frame)
{
	// Vertical movement
	if (_currentPosition.y > _previousPosition.y)
		_sprite.setTextureRect({ 0+ (int)_frame * 125, 0, 124, 124 });
	else if (_currentPosition.y < _previousPosition.y)
		_sprite.setTextureRect({ 0 + (int)_frame * 125, 0, 124, 124 });

	// Horizontal movement
	if (_currentPosition.x > _previousPosition.x)
		_sprite.setTextureRect({ 0 + (int)_frame * 124, 0, 124, 124 });
	else if (_currentPosition.x < _previousPosition.x)
		_sprite.setTextureRect({ 0 + (int)_frame * 124, 0, 124, 124 });
}

void HackerBoss::getFreezed()
{
	return;
}

void HackerBoss::moveHacker(int arr[][30])
{
	_frame += 0.08f;

	if (_frame > 8)
	{
		_frame = 0;
	}

	_previousPosition = _currentPosition;
	_currentPosition = getPosition();

	animation(_frame);

	switch (arr[(int)getPosition().y / 32][(int)getPosition().x / 32])
	{
	case 2:
		_direction = { _velocity.x,0.0f };
		break;
	case 3:
		_direction = { 0.0f,-_velocity.y };
		break;
	case 4:
		_direction = { 0.0f,_velocity.y };
		break;
	case 5:
		_direction = { 0.0f,-_velocity.y };
		break;
	case 8:
		_direction = { 0.0f,_velocity.y };
		_reachedEnd = true;
		break;
	case 9:
		_direction = { -_velocity.x,0.0f };
		_reachedEnd = true;
		break;
	default:
		_reachedEnd = false;
		break;
	}

	move(_direction);
}

int HackerBoss::attackUtn() {

	return 200;
}

void HackerBoss::saySth()
{
	if (!_bufferHacker.loadFromFile("music/TraineeSaySth.wav")) {
		throw std::runtime_error("Error al cargar Frase Hacker Dios");
	};
	_soundHacker.setBuffer(_bufferHacker);
	_soundHacker.setVolume(25);
	_soundHacker.play();
}