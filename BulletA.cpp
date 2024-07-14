#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "BulletA.h"

BulletA::BulletA(sf::Vector2f position, sf::Vector2f target, int damage)
{
	_type = 1;
	setScale({ 0.5f, 0.5f });
	setPosition(position);
	_enemyPosition = target;
	_damage = damage; //esto ver que valores segun la torre q le corresponde
	_speed = 6.f;
	loadTexture("img/bullets/iceball.png");
}

