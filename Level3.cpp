#include <iostream>
#include <cstdlib> // Necesario para std::rand() y std::srand()
#include <ctime> 
#include "UI.h"
#include "Map.h"
#include "Tower.h"
#include "TowerBrian.h"
#include "TowerKloster.h"
#include "TowerSarF.h"
#include "TowerWenner.h"
#include "HackerTrainee.h"
#include "HackerJunior.h"
#include "HackerSemiSr.h"
#include "HackerDios.h"
#include "Level.h"
#include "Spot.h"
#include "Level3.h"

Level3::Level3()
{
	_hackersPerWave = new int[3] { 14, 12, 10 };
	_wave1 = new int[14] { 4, 1, 1, 1, 3, 2, 2, 1, 3, 1, 1, 1, 3, 2 };
	_wave2 = new int[12] { 3, 1, 1, 2, 1, 4, 1, 1, 2, 1 ,1, 4 };
	_wave3 = new int[14] { 4, 2, 1, 1, 3, 1, 1, 1, 4, 1, 3, 1, 2, 3 };

	_currentWave = 1;
	_totalWaves = 3;
	_enemiesPerWave = 1;
	_timeBetweenWaves = 15;
	_waveClock.restart();
	_enemyClock.restart();
	_hackerStartPosition = { 960 / 32 * 9, 640 / 32 * 0 };
	_hackerStartPosition1 = { 960 / 32 * 9, 640 / 32 * 0.5 };
	_hackerStartPosition2 = { 960 / 32 * 20, 640 / 32 * 0 };

	_idLevel = 2;
	_finishedLevel = false;
	_map = new Map("img/maps/map3.png");;
	int arr[22][30] = {
{0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,6,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,6,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0,0,0,0,},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,1,4,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,9,},
{0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}
	};
	setMapArray(arr);

	_dying = false;
	if (!_textureUTN.loadFromFile("img/towers/facu.png")) {
		throw std::runtime_error("Error al cargar img UTN");
	};
	_UTN.setSize(sf::Vector2f(200, 173));
	_UTN.setTexture(&_textureUTN);
	_UTN.setPosition(sf::Vector2f(950, 400));
	_UTN.setOrigin(_UTN.getGlobalBounds().width / 2, _UTN.getGlobalBounds().height / 2);

	if (!_textureUTNRed.loadFromFile("img/towers/facuRed.png")) {
		throw std::runtime_error("Error al cargar img UTN");
	};
	_UTNRed.setSize(sf::Vector2f(200, 173));
	_UTNRed.setTexture(&_textureUTNRed);
	_UTNRed.setPosition(sf::Vector2f(950, 400));
	_UTNRed.setOrigin(_UTNRed.getGlobalBounds().width / 2, _UTNRed.getGlobalBounds().height / 2);

	setSpots(arr, _spots, 7);
	_golden = 900;
	_energy = 500;
	_ui.setText(0, std::to_string(getGolden()));
	_ui.setText(1, std::to_string(getEnergy()));
	_ui.setText(2, std::to_string(getCurrentWave()));
	_ui.setText(3, "/" + std::to_string(getTotalWaves()));

	_soundManager.stopMusic();
	_soundManager.loadMusic("music/level3.wav");
	_soundManager.setVolume(5);
	_soundManager.getMusicOn() ? _soundManager.playMusic() : _soundManager.stopMusic();

	_currentMenu = _menu1;

	setNoCoinsText();
	setLevelUpText();
}


