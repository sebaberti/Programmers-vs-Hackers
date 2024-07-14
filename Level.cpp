#include <iostream> //borrar
#include <vector>
#include <list>
#include "SFML/Graphics.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "FileLevel.h"
#include "MenuAbstract.h"
#include "UI.h"
#include "Map.h"
#include "Manager.h"
#include "TowerMenu.h"
#include "Spot.h"
#include "Tower.h"
#include "Hacker.h"
#include "HackerTrainee.h"
#include "HackerJunior.h"
#include "HackerSemiSr.h"
#include "HackerDios.h"
#include "HackerBoss.h"
#include "Level.h"

Level::Level()
	: _soundManager(SoundManager::getInstance())
{
}

//GETTERS
int Level::getIdLevel() const { return _idLevel; }

bool Level::getFinisheLevel() const { return _finishedLevel; }
UI Level::getUI() const { return _ui; }
Map Level::getMap() const { return *_map; }
int(*Level::getMapArray())[30] { return _mapArray; }
const std::vector<Spot*> Level::getSpots() const { return _spots; }
Spot* Level::getCurrentSpot() const { return _currentMenu->getCurrentSpot(); }

Spot* Level::getSpotByNumber(int n) const {
	for (auto& spot : _spots) {
		if (spot->getSpotNumber() == n) { return spot; }
	}
}
TowerMenu* Level::getCurrentMenu() const { return _currentMenu; }
int& Level::getGolden() { return _golden; }
int Level::getEnergy() { return _energy; }
int Level::getCurrentWave() { return _currentWave; }
int Level::getTotalWaves() { return _totalWaves; }
sf::SoundBuffer Level::getBuffer() const { return _buffer; }
sf::Sound Level::getSound() const { return _sound; }
bool Level::getMusicPlaying() const { return _musicPlaying; }
sf::Vector2f Level::getHackerStartPosition() const { return _hackerStartPosition; }
std::list<Tower*> Level::getActiveTowers() const { return _activeTowers; }

//SETTERS
void Level::setFinishedLevel(bool finished) { _finishedLevel = finished; }
void Level::setUI(const UI& ui) { _ui = ui; }
void Level::setMap(const Map& map) { *_map = map; }

void Level::setMapArray(const int(&mapArray)[22][30]) {
	std::copy(&mapArray[0][0], &mapArray[0][0] + 22 * 30, &_mapArray[0][0]);
}

void Level::setGolden(int golden) { _golden = golden; }
void Level::setEnergy(int energy) { _energy = energy; }
void Level::setMusicPlaying(bool playing) { _musicPlaying = playing; }
void Level::setSound(bool play) { play ? _sound.play() : _sound.pause(); }
void Level::setActiveTowers(Tower* tower) { _activeTowers.push_back(tower); }

void Level::setSpot(Spot* sp)
{
	for (auto& spot : _spots)
	{
		if (spot->getSpotNumber() == sp->getSpotNumber())
		{
			//si encuentra un objeto Spot con el mismo número de spot,
			//actualiza su estado ocupado  y la torre actual 
			spot->setOccupied(sp->getIsOccupied());
			spot->setCurrentTower(sp->getCurrentTower());
			break;
		}
	}
}

void Level::setSpots(int arr[][30], std::vector<Spot*>& spots, int cant) {
	for (int i = 0; i < cant; i++)
	{
		Spot* sp = new Spot();
		spots.push_back(sp);
	}

	//Ubicar spots
	int index = 0;
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (arr[y][x] == 6 && index < cant)
			{
				spots[index]->setPosition(32 * x, 32 * y);
				spots[index]->setSpotNumber(index + 1);
				index++;
			}
		}
	}
}

void Level::setCurrentSpot(Spot* sp) { _currentMenu->setCurrentSpot(sp); }

//establece el objeto _currentMenu con el puntero proporcionado(menu).
//permite cambiar dinámicamente el menú actual que se está utilizando en el nivel

void Level::setCurrentMenu(TowerMenu* menu) { _currentMenu = menu; }

void Level::setCurrentMenu(Spot* currentSp)
{
	_currentMenu->setCurrentSpot(currentSp); //guardo el nro de spot en el tower Menu2;
	_currentMenu->setCurrentTower(currentSp->getCurrentTower());

	//configurar el boton en el indice 0 el menu actual
	setInfoBtn(_currentMenu, currentSp, 0); //debe recibir Tw*, *_currentMenu e Index

	if (_currentMenu->getNumberMenu() == 2) {  //solo en el menu 2 se setea upgrade
		setInfoBtn(_currentMenu, currentSp, 1);
	}
	_currentMenu->setPosition(currentSp->getPosition());
}

void Level::setInfoBtn(TowerMenu* menu, Spot* currentSp, int index)
{
	Tower* tower = currentSp->getCurrentTower();
	Button* btn = _currentMenu->getButtonByIndex(index);

	if (index == 1) {
		btn->setPrice(tower->getPriceUpgrade());
		btn->setDamage(tower->getDamageUpgrade());
		btn->setFireRate(tower->getFireRate());
		btn->setInfo();
	}
	else {
		btn->setPrice(tower->getSalesValue());
	}
	btn->setPriceText();
}

void Level::setNoCoinsText()
{
	if (!_fontNoCoins.loadFromFile("fuentes/TowerPrice.ttf"))
	{
		throw std::runtime_error("Error al cargar la fuente del Price Menu \n");
	}

	_NoCoins.setFont(_fontNoCoins);
	_NoCoins.setCharacterSize(70);
	_NoCoins.setOrigin(_NoCoins.getGlobalBounds().getPosition().x / 2, _NoCoins.getGlobalBounds().height / 2);
	_NoCoins.setPosition(250, 250);
	_NoCoins.setFillColor(sf::Color(255, 0, 0));
	_NoCoins.setString("SALDO INSUFICIENTE");

	_noCoinsClock.restart();
	_displayTimeNoCoins = sf::seconds(3);
	_flagNoCoins = false;
}

void Level::setLevelUpText()
{
	if (!_fontLevelUp.loadFromFile("fuentes/TowerPrice.ttf"))
	{
		throw std::runtime_error("Error al cargar la fuente del Level Up");
	}
	_levelUp.setFont(_fontLevelUp);
	_levelUp.setCharacterSize(70);
	_levelUp.setOrigin(_levelUp.getGlobalBounds().getPosition().x / 2, _levelUp.getGlobalBounds().height / 2);
	_levelUp.setPosition(350, 250);
	_levelUp.setFillColor(sf::Color(0, 0, 255));
	_levelUp.setString("CONGRATS! \n LEVEL UP");

	_congrats.setFont(_fontLevelUp);
	_congrats.setCharacterSize(90);
	_congrats.setOrigin(_levelUp.getGlobalBounds().getPosition().x / 2, _levelUp.getGlobalBounds().height / 2);
	_congrats.setPosition(350, 250);
	_congrats.setFillColor(sf::Color(0, 255, 0));
	_congrats.setString("CONGRATS! \n YOU WIN");
}

void Level::spawnWave() {
	std::srand(std::time(nullptr));
	
	//puntero a obj Hacker para almacenar el nuevo enemigo
	Hacker* hk;

	if (_enemyIndex < _enemiesPerWave) {
		// Genera un nuevo enemigo
		float newRandom = std::rand() % 420 * 0.01f + 0.4f;

		while (_enemiesRandomTime == newRandom) {
			newRandom = std::rand() % 420 * 0.01f + 0.4f;
		}
		_enemiesRandomTime = newRandom;

		if (_enemyClock.getElapsedTime().asMilliseconds() *0.001f >= _enemiesRandomTime) {
			switch (_currentWave)
			{
			case 1:
			{
				hk = returnHacker(_wave1[_enemyIndex]);
			}
			break;
			case 2:
			{
				hk = returnHacker(_wave2[_enemyIndex]);
			}
			break;
			case 3:
			{
				hk = returnHacker(_wave3[_enemyIndex]);
			}
			break;
			case 4:
			default:
			{
				hk = returnHacker(_wave4[_enemyIndex]);
			}
			break;
			}

			hk->setPosition(_hackerStartPosition);
			_enemies.push_back(hk);

			if (_enemyIndex == 0) {
				hk->saySth();
			}
			++_enemyIndex;
			if (_currentWave > 1) {
				_enemyIndex % 3 == 0 ? _hackerStartPosition = _hackerStartPosition1 : _hackerStartPosition = _hackerStartPosition2;
			}
			_enemyClock.restart();
		}
	}
	//si se cumplio el tiempo entre oleadas y si no queda ninguna enemigo de la ola actual
	else if (_waveClock.getElapsedTime().asSeconds() > _timeBetweenWaves && _enemies.empty() && _enemyIndex == _enemiesPerWave) {
		++_currentWave; // Incrementa el número de oleada
		_enemyIndex = 0; // Reinicia el índice para la próxima oleada
		if (_currentWave <= _totalWaves) {
			_currentWave % 2 != 0 ? _hackerStartPosition = _hackerStartPosition1 : _hackerStartPosition = _hackerStartPosition2;
			_enemiesPerWave = _hackersPerWave[_currentWave - 1]; // Actualiza la cantidad de enemigos para la próxima oleada
			_ui.setText(2, std::to_string(getCurrentWave()));
			_waveClock.restart(); // Reinicia el temporizador de la oleada
		}
	}
}

void Level::decreaseEnergy(int amount) {
	_energy -= amount;
}

void Level::mouseCheck(sf::Vector2i& mousePosition)
{
	sf::Vector2f transformedMousePos = getInverseTransform().transformPoint(sf::Vector2f(mousePosition));
	
	for (auto& spot : _spots)
	{
		spot->mouseCheck(transformedMousePos);
	}

	if (_currentMenu->getIsVisible() && _currentMenu->getGlobalBounds().contains(transformedMousePos))
	{
		_currentMenu->mouseCheck(mousePosition);
	}

}

bool Level::validateSale(Tower* tower, bool firstSale) {
	int	price;
	if (firstSale)
		price = tower->getPrice();
	else
		price = tower->getPriceUpgrade();

	if (price <= getGolden()) {
		_flagNoCoins = false;
		return true;
	}
	_flagNoCoins = true;
	return false;
}

void Level::sell(Tower* tower, Spot& currentSpot) {
	int price;
	if (currentSpot.getIsOccupied()) { price = tower->getPriceUpgrade(); }
	else { price = tower->getPrice(); }

	setGolden(getGolden() - price);

	_ui.setText(0, std::to_string(getGolden()));
	currentSpot.setCurrentTower(tower);
	currentSpot.setOccupied(true);
}

void Level::resellTower(Spot& sp) {
	Tower* tower = sp.getCurrentTower();
	int resaleValue = tower->getSalesValue();
	setGolden(getGolden() + resaleValue); // Agregar el valor de reventa al oro del jugador

	_ui.setText(0, std::to_string(getGolden()));
	sp.clearCurrentTower(); // Limpiar la torre del spot
	sp.setOccupied(false); // Marcar el spot como no ocupado
	_activeTowers.remove(tower);

}

Hacker* Level::returnHacker(int type) {
	switch (type)
	{
	case 1:
		return new HackerTrainee;
		break;
	case 2:
		return new HackerJunior;
		break;
	case 3:
		return new HackerSemiSr;
		break;
	case 4:
		return new HackerDios;
		break;
	case 5:
		return new HackerBoss;
		break;
	}
}

void Level::shoot(sf::Vector2f shootingPosition, sf::Vector2f targetPosition, int damage, int type, Hacker* hacker)
{
	switch (type)
	{
	case 1:
		_bullets.push_back(new BulletA(shootingPosition, targetPosition, damage));
		break;
	case 2:
		_bullets.push_back(new BulletB(shootingPosition, targetPosition, damage));
		break;
	case 3:
		_bullets.push_back(new BulletC(shootingPosition, targetPosition, damage));
		break;
	case 4:
		_bullets.push_back(new BulletD(shootingPosition, targetPosition, damage));
		break;
	}
}


void Level::checkLevelCompletion()
{
	if (_currentWave > _totalWaves && _enemies.empty())
	{
		_finishedLevel = true;
		_levelUpClock.restart();
		_soundManager.stopMusic();
		_soundManager.loadMusic("music/menuMusic.wav");

		//abrir el archivo de niveles y actualizar el estado del próximo si no es el último
		if (_idLevel < 4)
		{  // cuando llega al ultimo nivel no se abre el archivo
			FileLevels arc;
			Levels reg;

			reg = arc.read(_idLevel + 1);
			reg.setStatus(true);
			arc.edit(reg, _idLevel + 1);
		}
	}
}

void Level::setGameOverText()
{
	if (!_fontGameOver.loadFromFile("fuentes/TowerPrice.ttf")) {
		throw std::runtime_error("Error al cargar la fuente del Price Menu");
	}
	_gameOver.setFont(_fontGameOver);
	_gameOver.setCharacterSize(70);
	_gameOver.setPosition(300, 250);
	_gameOver.setFillColor(sf::Color(255, 0, 0));
	_gameOver.setString("GAME OVER");

	if (!_textureGameOverSkull.loadFromFile("img/complementarias/Rip.png")) {
		throw std::runtime_error("Error al cargar la calavera de GameOver");
	}
	_gameOverSkull.setTexture(_textureGameOverSkull);
	_gameOverSkull.setPosition(400, 150);
	_gameOverSkull.setScale(0.5, 0.5);
	_gameOverSkull.setOrigin(_gameOverSkull.getGlobalBounds().width / 2, _gameOverSkull.getGlobalBounds().height / 2);
	_gameOverClock.restart();
	_soundManager.stopMusic();
	_soundManager.loadMusic("music/menuMusic.wav");
}

void Level::update(sf::Vector2i& mousePosition, int& view) {
	if (!_finishedLevel) {
		checkLevelCompletion(); //xq quiero que una sola vez pase por el check level si se gana el nivel, ya que ahi reseteo un clock
		if (!_finishedLevel) {
			if (!_flagGameOver) {
				mouseCheck(mousePosition);

				if (_currentWave <= _totalWaves)
				{
					spawnWave(); // Generar una nueva oleada de enemigos
				}

				updateHackers();
				updateSpots();
				updateBullets();
				updateEnemies();

				if (_currentMenu->getIsVisible())
				{
					_currentMenu->update(mousePosition);
				}
			}
			else {
				if (_gameOverClock.getElapsedTime().asSeconds() > 5) {
					MenuAbstract::getInstance().setNumberMenu(2);
					view = 1;
				}
			}
		}
	}
	else if (_levelUpClock.getElapsedTime().asSeconds() > 4) {
		MenuAbstract::getInstance().setNumberMenu(2);
		view = 1;
	}
}

void Level::updateBullets()
{
	auto it = _bullets.begin();
	while (it != _bullets.end())
	{
		Bullet* bullet = *it;
		bool bulletErased = false;

		for (auto& hacker : _enemies)
		{
			if (bullet->getTransform().transformRect(bullet->getBounds()).intersects(hacker->getBounds()))
			{
				hacker->takeDamage(bullet->getDamage(), bullet->getType());
				delete bullet;
				bulletErased = true;

				it = _bullets.erase(it);
				break;
			}
		}

		if (!bulletErased)
		{
			sf::Vector2f lastPosition = bullet->getPosition();

			bullet->update();
			bullet->update();

			if (bullet->getPosition() == lastPosition)
			{
				delete bullet;
				it = _bullets.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void Level::updateHackers()
{
	for (auto& hacker : _enemies) {
		hacker->update(getMapArray());

		if (hacker->getEnd() == true) {
			if (getEnergy() - hacker->attackUtn() >= 0) {
				_dying = true;
				decreaseEnergy(hacker->attackUtn());
			}
			else {
				setEnergy(0);
				_flagGameOver = true;
				setGameOverText();
			}
			_ui.setText(1, std::to_string(getEnergy()));
			break; // Si encontramos un enemigo en el final, no necesitamos seguir buscando
		}
		else {
			_dying = false;
		}
	}
}

void Level::updateSpots() {
	for (auto& spot : _spots)
	{
		for (auto& hacker : _enemies)
		{
			if (spot->getIsOccupied() && spot->getTransform().transformRect((spot->getCurrentTower()->getBounds())).intersects(hacker->getBounds()))
			{
				if (spot->getCurrentTower()->canShoot())
				{
					shoot(spot->getPosition(),
						hacker->getPosition(),
						spot->getCurrentTower()->getDamage(),
						spot->getCurrentTower()->getType(), hacker);
				}
			}
		}
	}
}

void Level::updateEnemies() {
	auto itH = _enemies.begin();
	while (itH != _enemies.end())
	{
		Hacker* hacker = *itH;
		hacker->update(getMapArray());
		if (hacker->getLife() <= 0)
		{
			setGolden(getGolden() + hacker->getGoldenDrop());
			_ui.setText(0, std::to_string(getGolden()));

			itH = _enemies.erase(itH);
		}
		else
		{
			++itH;
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	states.transform *= getTransform();
	target.draw(*_map, states);
	_dying ? target.draw(_UTNRed, states) : target.draw(_UTN, states);
	target.draw(_ui, states);
	for (Spot* spot : _spots)
	{
		target.draw(*spot, states);
	}
	if (!_finishedLevel) {
		if (!_flagGameOver) {
			for (const auto& hacker : _enemies)
			{
				if (hacker->getLife() > 0) {
					target.draw(*hacker, states);
				}
			}
			if (_currentMenu->getIsVisible())
			{
				target.draw(*_currentMenu, states);
			}
			for (auto& bullet : _bullets)
			{
				target.draw(*bullet, states);
			}
			if (_noCoinsClock.getElapsedTime() < _displayTimeNoCoins && _flagNoCoins) {
				target.draw(_NoCoins, states); // Dibujar el texto
			}
		}
		else {
			target.draw(_gameOverSkull, states);
			target.draw(_gameOver, states);
		}
	}
	else {
		_idLevel != 4 ? target.draw(_levelUp, states) : target.draw(_congrats, states);
	}

}
Level::~Level() { //eliminar todo lo que haya sido asignado con memoria dinamica
	delete _menu1;
	delete _menu2;
	delete _menu3;

	delete[] _hackersPerWave;
	delete[] _wave1;
	delete[] _wave2;
	delete[] _wave3;
	delete[] _wave4;

	for (Hacker* hacker : _enemies) {
		delete hacker;
	}

	for (Tower* tower : _activeTowers) {
		delete tower;
	}

	for (Bullet* bullet : _bullets) {
		delete bullet;
	}

	delete _map;

	for (Spot* spot : _spots) {
		delete spot;
	}
}