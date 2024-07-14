#include "TowerWenner.h"
#include "Level.h"
#include "Spot.h"
#include "Level4.h"

Level4::Level4()
{
	_hackersPerWave = new int[4] { 8, 10, 11, 11 };
	_wave1 = new int[8] { 1, 1, 1, 2, 2, 2, 3, 1};
	_wave2 = new int[10] { 3, 2, 1, 1, 2, 2, 1, 3, 1, 1};
	_wave3 = new int[11] { 3, 2, 1, 1, 3, 2, 2, 2, 1, 3, 3};
	_wave4 = new int[11] { 2, 1, 2, 3, 2, 2, 2, 2, 1, 3, 4};

	_currentWave = 1;
	_totalWaves = 4;
	_enemiesPerWave = 4;
	_timeBetweenWaves = 15;
	_waveClock.restart();
	_enemyClock.restart();
	_hackerStartPosition = { 960 / 32 * 4, 640 / 32 * 0 };
	_hackerStartPosition1 = _hackerStartPosition;
	_hackerStartPosition2 = _hackerStartPosition;

	_idLevel = 3;
	_finishedLevel = false;
	_map = new Map("img/maps/map4.png");;
	int arr[22][30] = {
{0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,6,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,6,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,6,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,6,0,0,2,1,1,1,9,9},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,2,1,1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

	setSpots(arr, _spots, 4);
	_golden = 500;
	_energy = 600;
	_ui.setText(0, std::to_string(getGolden()));
	_ui.setText(1, std::to_string(getEnergy()));
	_ui.setText(2, std::to_string(getCurrentWave()));
	_ui.setText(3, "/" + std::to_string(getTotalWaves()));

	_soundManager.stopMusic();
	_soundManager.loadMusic("music/level4.wav");
	_soundManager.setVolume(15);
	_soundManager.getMusicOn() ? _soundManager.playMusic() : _soundManager.stopMusic();

	_currentMenu = _menu1;

	setNoCoinsText();
	setLevelUpText();
}