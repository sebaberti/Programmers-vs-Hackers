#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "BulletD.h"

BulletD::BulletD(sf::Vector2f position, sf::Vector2f target, int damage)
{
	_type = 4;
	setPosition(position);
	setScale({ 0.5f, 0.5f });
	_enemyPosition = target;
	_damage = damage; //esto ver que valores segun la torre q le corresponde
	_speed = 6.f;
	loadTexture("img/bullets/shadowball.png");
}

