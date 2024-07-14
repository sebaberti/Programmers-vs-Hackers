#include <SFML/Graphics.hpp>
#include <iostream> //borrar
#include "Hacker.h"
#include "Tower.h"
#include "TowerKloster.h"

TowerKloster::TowerKloster()
{
	if (!_texture.loadFromFile("img/towers/torreC_2.png")) {
		throw std::runtime_error("Error img Tower Kloster");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_name = "Torre SPD";

	//Rango de ataque:
	_visualRange.setRadius(130);
	_visualRange.setFillColor(sf::Color(0, 255, 0, 30));
	_visualRange.setOrigin(_visualRange.getGlobalBounds().width / 2, _visualRange.getGlobalBounds().height / 2);

	_type = 2;
	_price = 100;
	_priceUpgrade = 110;
	_salesValue = 80;
	_damage = 7;
	_damageUpgrade = 9;
	_upgradesAmount = 2;
	_fireRate = 2.0f; // Tiempo en segundos entre disparos
	_fireRateUpgrade = 1.5f;
	_clock.restart();
}

Tower* TowerKloster::clone() const { return new TowerKloster(); }

void TowerKloster::sayHi()
{
	if (!_bufferTeacher.loadFromFile("music/KlosterHi.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerKloster::sayBye()
{
	if (!_bufferTeacher.loadFromFile("music/KlosterBye.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerKloster::upgrade()
{
	switch (_upgradesAmount)
	{
	case 2:
	{
		_name = "ARSO";
		if (!_texture.loadFromFile("img/towers/torreC_3.png")) {
			throw std::runtime_error("Error img tower ARSO");
		}
		_sprite.setTexture(_texture);
		_priceUpgrade = 200;
		_salesValue = 168;
		_damage = 9;
		_damageUpgrade = 13;
		_fireRate = 1.5f; //dispara mas rapido
		_fireRateUpgrade = 1.f;
		_upgradesAmount = 1;
	}
	break;
	case 1:
	{
		_name = "Torre KLOSTER";
		if (!_texture.loadFromFile("img/towers/torrec_4.png")) {
			throw std::runtime_error("Error img tower Labo3 BRIAN");
		}
		_sprite.setTexture(_texture);

		_priceUpgrade = 9990;
		_salesValue = 328;
		_damage = 13;
		_fireRate = 1.2f;
		_upgradesAmount = 0;
	}
	default:
		break;
	}
}
