#include <SFML/Graphics.hpp>
#include <iostream> //borrar
#include "Hacker.h"
#include "Tower.h"
#include "TowerSarF.h"

TowerSarF::TowerSarF() //elimine sf::Vector2f position   del argumento
{
	if (!_texture.loadFromFile("img/towers/torreD_1.png")) {
		throw std::runtime_error("Error img Sar F");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

	_name = "Torre Programacion 1";

	//Rango de ataque:
	_visualRange.setRadius(140);
	_visualRange.setFillColor(sf::Color(0, 255, 0, 30));
	_visualRange.setOrigin(_visualRange.getGlobalBounds().width / 2, _visualRange.getGlobalBounds().height / 2);

	_type = 3;
	_price = 180;
	_priceUpgrade = 240;
	_salesValue = 144;
	_damage = 7;
	_damageUpgrade = 5;
	_upgradesAmount = 2;
	_fireRate = 1.0f; // Tiempo en segundos entre disparos
	_fireRateUpgrade = 1.7f;
	_clock.restart();
}

Tower* TowerSarF::clone() const { return new TowerSarF(); }

void TowerSarF::sayHi()
{
	if (!_bufferTeacher.loadFromFile("music/SarFHi.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerSarF::sayBye()
{
	if (!_bufferTeacher.loadFromFile("music/SarFBye.wav")) {
		throw std::runtime_error("Error al cargar Saludo Kloster");
	};
	_soundTeacher.setBuffer(_bufferTeacher);
	_soundTeacher.setVolume(25);
	_soundTeacher.play();
}

void TowerSarF::upgrade()
{
	switch (_upgradesAmount)
	{
	case 2:
	{
		_name = "Programacion 2";
		if (!_texture.loadFromFile("img/towers/torreD_2.png")) {
			throw std::runtime_error("Error img tower Programacion2");
		}
		_sprite.setTexture(_texture);
		_priceUpgrade = 300;
		_salesValue = 336;
		_damage = 5;
		_damageUpgrade = 7;
		_fireRate = 1.7f; //dispara mas rapido
		_fireRateUpgrade = 1.5f;
		_upgradesAmount = 1;
	}
	break;
	case 1:
	{
		_name = "Torre MAXI F";
		if (!_texture.loadFromFile("img/towers/torreD_3.png")) {
			throw std::runtime_error("Error img tower MAXI F");
		}
		_sprite.setTexture(_texture);

		_priceUpgrade = 9990;
		_salesValue = 576;
		_damage = 7;
		_fireRate= 1.5f;
		_upgradesAmount = 0;
	}
	default:
		break;
	}
}

