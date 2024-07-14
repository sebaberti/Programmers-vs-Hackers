#include <SFML/Graphics.hpp>
#include <iostream> //borrar
#include "Hacker.h"
#include "Tower.h"
#include "TowerWenner.h"

TowerWenner::TowerWenner()
{
	if (!_texture.loadFromFile("img/towers/torreB_3.png")) {
		throw std::runtime_error("Error img Tower Wenner");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_name = "wenner";

	//Rango de ataque:
	_visualRange.setRadius(120);
	_visualRange.setFillColor(sf::Color(0, 255, 0, 30));
	_visualRange.setOrigin(_visualRange.getGlobalBounds().width / 2, _visualRange.getGlobalBounds().height / 2);

	_type = 4;
	_price = 150;
	_priceUpgrade = 200;
	_salesValue = 120;
	_damage = 8;
	_damageUpgrade = 14;
	_upgradesAmount = 2;
	_fireRate = 1.5f; // Tiempo en segundos entre disparos
	_fireRateUpgrade = 1.5f;
	_clock.restart();
}

Tower* TowerWenner::clone() const { return new TowerWenner(); }

void TowerWenner::sayHi()
{
	if (!_bufferTeacher.loadFromFile("music/WennerHi.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerWenner::sayBye()
{
	if (!_bufferTeacher.loadFromFile("music/WennerBye.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerWenner::upgrade()
{
	switch (_upgradesAmount)
	{
	case 2:
	{
		_name = "estadistica";
		if (!_texture.loadFromFile("img/towers/torreB_4.png")) {
			throw std::runtime_error("Error img tower estadistica");
		}
		_sprite.setTexture(_texture);

		_priceUpgrade = 300;
		_salesValue = 280;
		_damage = 14;
		_damageUpgrade = 20;
		//fireRate se mantiene
		_fireRateUpgrade = 2.f;
		_upgradesAmount = 1;
	}
	break;
	case 1:
	{
		_name = "Torre WENNER";
		if (!_texture.loadFromFile("img/towers/torreb_5.png")) {
			throw std::runtime_error("Error img tower MAXI WENNER");
		}
		_sprite.setTexture(_texture);

		_priceUpgrade = 9990;
		_salesValue = 816;
		_damage = 20;
		_fireRate = 2.f; //se hace mas lento
		_upgradesAmount = 0;
	}
	default:
		break;
	}
}