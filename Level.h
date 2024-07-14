#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "UI.h"
#include "Map.h"
#include "TowerMenu.h"
#include "TowerMenu1.h"
#include "TowerMenu2.h"
#include "TowerMenu3.h"
#include "Tower.h"
#include "Spot.h"
#include "Bullet.h"
#include "BulletA.h"
#include "BulletB.h"
#include "BulletC.h"
#include "BulletD.h"

#include "SoundManager.h"

class Level: public sf::Drawable, public sf::Transformable
{
protected:
	int _idLevel;
	bool _finishedLevel;
	UI _ui;
	sf::Texture _textureUTN;
	sf::RectangleShape _UTN;
	sf::Texture _textureUTNRed;
	sf::RectangleShape _UTNRed;
	bool _dying;

	Map* _map;
	int _mapArray[22][30];
	std::vector<Spot*> _spots;
	TowerMenu* _currentMenu;
	TowerMenu1* _menu1 = new TowerMenu1();
	TowerMenu2* _menu2 = new TowerMenu2();
	TowerMenu3* _menu3 = new TowerMenu3();
	int _golden;
	int _energy;
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	bool _musicPlaying;

	SoundManager& _soundManager;

	int *_hackersPerWave;
	int *_wave1;
	int *_wave2;
	int *_wave3;
	int *_wave4;


	std::vector<Hacker*> _enemies;
	int _enemyIndex;
	int _currentWave;
	int _totalWaves;
	int _enemiesPerWave;
	int _timeBetweenWaves;
	int _timeBetweenEnemies;
	sf::Clock _waveClock;
	sf::Clock _enemyClock;
	float _enemiesRandomTime= std::rand() % 320 * 0.01f + 0.4f;

	sf::Vector2f _hackerStartPosition;
	sf::Vector2f _hackerStartPosition1;
	sf::Vector2f _hackerStartPosition2;
	//std::list <Tower*> _towersAvailable;
	std::list <Tower*> _activeTowers;

	std::list<Bullet*> _bullets;

	//NUEVO:
	sf::Font _fontNoCoins;
	sf::Clock _noCoinsClock;
	sf::Text _NoCoins;
	sf::Time _displayTimeNoCoins;
	bool _flagNoCoins;
	sf::Font _fontGameOver;
	sf::Text _gameOver;
	sf::Texture _textureGameOverSkull;
	sf::Sprite _gameOverSkull;
	bool _flagGameOver;
	sf::Clock _gameOverClock;
	sf::Font _fontLevelUp;
	sf::Clock _levelUpClock;
	sf::Text _levelUp;
	sf::Text _congrats;
public:
	Level();
	void spawnWave();
	int getIdLevel() const;
	bool getFinisheLevel()const;
	UI getUI() const;
	Map getMap() const;
	int(*getMapArray())[30];
	const std::vector<Spot*> getSpots() const;
	Spot* getCurrentSpot() const;
	Spot* getSpotByNumber(int) const;
	TowerMenu* getCurrentMenu() const;
	//Cambié acá por refrefencia
	int& getGolden();
	int getEnergy();
	int getCurrentWave();
	int getTotalWaves();
	sf::SoundBuffer getBuffer() const;
	bool getMusicPlaying() const;
	sf::Sound getSound() const;
	sf::Vector2f getHackerStartPosition() const;
	//const std::list<Tower*> getTowersAvailable() const;
	std::list <Tower*> getActiveTowers() const;

	//void setIdLevel(int);
	void setFinishedLevel(bool);
	void setUI(const UI&);
	void setMap(const Map&);
	void setMapArray(const int(&)[22][30]);
	void setGolden(int);
	void setEnergy(int);
	void setMusicPlaying(bool);
	void setSound(bool);
	//void setTowersAvailable(Tower*);
	void setActiveTowers(Tower*);
	void setSpot(Spot*);
	void setSpots(int arr[][30], std::vector<Spot*>&, int);
	void setCurrentSpot(Spot*); //para que el currentMenu tenga su Spot asociado
	void setCurrentMenu(TowerMenu*);
	void setCurrentMenu(Spot*);  //SOBRECARGA DE FUNCION
	void setInfoBtn(TowerMenu*, Spot*, int);
	void setNoCoinsText();
	void setLevelUpText();


	void mouseCheck(sf::Vector2i&);
	void validateClick(int, int, int&);
	int validateClickOnSpot(int, int);
	void manageClickOnSpot(int, int, Spot*, int);
	void manageOutOfSpotClick(int, int); //DEBERIA SER PUNTERO??????
	void clickWithMenu1Open(int, int, Spot&);
	void clickWithMenu2Open(int, int, Spot&);
	void validateClickOnSpeaker(int, int);
	void validateClickOnHome(int, int, int&);

	bool validateSale(Tower*, bool);
	void sell(Tower*, Spot&);
	void resellTower(Spot&);
	void decreaseEnergy(int);

	Hacker* returnHacker(int);
	void shoot(sf::Vector2f, sf::Vector2f, int, int, Hacker*);
	void checkLevelCompletion();
	void setGameOverText();

	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void update(sf::Vector2i&, int&);
	void updateBullets();
	void updateHackers();
	void updateSpots();
	void updateEnemies();

	~Level();
};

