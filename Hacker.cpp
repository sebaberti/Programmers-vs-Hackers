#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Hacker.h"

int Hacker::getLife() const { return _life; }
sf::Vector2f Hacker::getVelocity() const { return _velocity; }
sf::Vector2f Hacker::getDirection() const { return _direction; }
bool Hacker::getBoss() const { return _isABoss; }
int Hacker::getGoldenDrop() const { return _goldenDrop; }
bool Hacker::getEnd() const { return _reachedEnd; }

void Hacker::setEnd(bool end) { _reachedEnd = end; }
void Hacker::setLife(int life) { _life = life; }
void Hacker::setVelocity(sf::Vector2f velocity) { _velocity = velocity; }
void Hacker::setDirection(sf::Vector2f direction) { _direction = direction; }
void Hacker::setBoos(bool boss) { _isABoss = boss; }
void Hacker::setGoldenDrop(int drop) { _goldenDrop = drop; }

void Hacker::takeDamage(int damageBullet, int type)
{
	//bala de tipo 4 efecto de congelamiento
	if (type == 1)
	{
		getFreezed();
	}
	//tipo de enemigo es del mismo tipo de la bala le causa mas danio
	if (_type == type)
	{
		_life -= damageBullet * 1.7;
	}
	else
	{
		_life -= damageBullet;

	}

}

void Hacker::animation(float _frame)
{
	//Vertical ascendente
	if (_currentPosition.y > _previousPosition.y)
		_sprite.setTextureRect({ 0 + (int)_frame * 64, 0, 64, 64 });
	//descendente
	if (_currentPosition.y < _previousPosition.y)
		_sprite.setTextureRect({ 0 + (int)_frame * 64, 192, 64, 64 });

	//Horozontal derecha
	if (_currentPosition.x > _previousPosition.x)
		_sprite.setTextureRect({ 0 + (int)_frame * 64, 128, 64, 64 });
	//izquierda
	if (_currentPosition.x < _previousPosition.x)
		_sprite.setTextureRect({ 0 + (int)_frame * 64, 64, 64, 64 });

}

void Hacker::moveHacker(int arr[][30])
{
	//animacion mas lenta
	_isFreezed ? _frame += 0.02f : _frame += 0.2f;

	if (_frame > 4)
	{
		_frame = 0;
	}

	_previousPosition = _currentPosition;
	_currentPosition = getPosition();


	if (_isFreezed)
	{
		_sprite.setColor(sf::Color(135, 206, 250, 255));
	}

	animation(_frame);

	switch (arr[(int)getPosition().y / 32] [(int)getPosition().x / 32])
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
		_direction = { 0.0f,-_velocity.y};
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

sf::FloatRect Hacker::getBounds() const { return getTransform().transformRect(_sprite.getGlobalBounds()); }

void Hacker::update(int arr[][30])
{
	moveHacker(arr);
}

void Hacker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

void Hacker::getFreezed()
{
	if (!_isFreezed)
	{
		_isFreezed = true;
		_velocity *= 0.5f;
	}
}
