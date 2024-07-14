#include <iostream> //borrar
#include <vector>
#include <list>
#include "SFML/Graphics.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "MenuAbstract.h"
#include "UI.h"
#include "Map.h"
#include "Manager.h"
#include "TowerMenu.h"
#include "Spot.h"
#include "Tower.h"
#include "Level.h"

void Level::validateClick(int mousex, int mousey, int& view)
{
	Spot* currentSpot;
	int clickSpot = validateClickOnSpot(mousex, mousey);

	if (clickSpot != 0)
	{ //si se clickeo spot, esto devuelve el nro de spot
		currentSpot = getSpotByNumber(clickSpot);
		manageClickOnSpot(mousex, mousey, currentSpot, clickSpot); //currentSpot tiene el nro de spot y el estado
	}
	else if (_currentMenu->getCurrentSpot() != nullptr) //quiza es mi primer click y no tengo spot
	{ //si NO se clickeo spot
		currentSpot = _currentMenu->getCurrentSpot();
		manageOutOfSpotClick(mousex, mousey);
	}

	//parlante
	validateClickOnSpeaker(mousex, mousey);
	//home
	validateClickOnHome(mousex, mousey, view);
}


int Level::validateClickOnSpot(int mousex, int mousey)
{
	//vemos si el menu no esta visible, se puede interactuar con los spots 
	if (!_currentMenu->getIsVisible()) {
		for (auto& spot : _spots) {
			if (spot->getGlobalBounds().contains(mousex, mousey)) {
				return spot->getSpotNumber();
			}
		}
	}
	return 0;  //seria como decir "no se clickeo en ningun spot"
}


void Level::manageClickOnSpot(int mousex, int mousey, Spot* currentSpot, int clickSpot) {
	//numero de spot seleccionado y estado de ocupacion
	currentSpot->setSpotNumber(clickSpot);
	currentSpot->setOccupied(getSpotByNumber(currentSpot->getSpotNumber())->getIsOccupied());

	//asignar el spot actual al menu actual
	_currentMenu->setCurrentSpot(currentSpot);  //si se clickeo en spot le estoy diciendo a menu q se asocie a ese spot

	//Transformar las coordenadas del mouse a las coordenadas locales del nivel
	sf::Vector2f transformedMousePos = getInverseTransform().transformPoint(mousex, mousey);

	//posición del menú actual en las coordenadas transformadas
	_currentMenu->setPosition(transformedMousePos);

	//verificamos si esta ocupado
	if (currentSpot->getIsOccupied()) {
		currentSpot->getCurrentTower()->getUpgradesAmount() != 0 ? _currentMenu = _menu2 : _currentMenu = _menu3;
		setCurrentMenu(currentSpot);  //Menu2 o 3 segun corresponda
	}
	else
	{  //spot libre
		_currentMenu = _menu1;
		//me aseguro que el currentSpot esta asociado a la tower ahora
		//asigno la torre actual del menú actual al spot actual.
		currentSpot->setCurrentTower(_currentMenu->getCurrentSpot()->getCurrentTower());
		_currentMenu->setPosition(currentSpot->getPosition());
	}

	_currentMenu->getIsVisible() ? _currentMenu->hide() : _currentMenu->show();
	setCurrentSpot(currentSpot);
	setSpot(currentSpot);
}


//CLICKS FUERA DEL SPOT MIENTRAS ALGUN MENU ESTA VISIBLE 
void Level::manageOutOfSpotClick(int mousex, int mousey) {

	if (_currentMenu->getIsVisible())
	{
		Spot* sp;
		//click fuera de spot y towerMenu estaba visible
		sp = _currentMenu->getCurrentSpot(); //sp ya viene con su nro q se seteo previamente al hacer click en el spot

		if (_currentMenu->getNumberMenu() == 1)
		{
			clickWithMenu1Open(mousex, mousey, *sp);
			
		}
		else
		{
			clickWithMenu2Open(mousex, mousey, *sp);
			
		}

		//guardo la informacion del spot en el Menu
		_currentMenu->setCurrentSpot(sp);
		setSpot(sp);
	}
}

//CLICKS EN EL MENU 1
void Level::clickWithMenu1Open(int mousex, int mousey, Spot& sp)
{
	//verificamos si se clickeo un boton del menu
	Button* btn = _currentMenu->validateClickOnButton(mousex, mousey, sp);

	if (btn->getBtnNumber() != -1) {  //se hizo click en un boton

		/// Validar si se puede comprar la torre asociada al botón
		if (validateSale(btn->getTower(), true)) {

			// Crear una nueva instancia de la torre
			Tower* tower = btn->getTower()->clone();
			sell(tower, sp);

			tower->setSpotNumber(sp.getSpotNumber());
			tower->setPosition(0, 0);
			tower->sayHi();
			setActiveTowers(tower);
			setSpot(&sp);
		}
		else {
			//reseteo el clock para que se muestre el cartel de Saldo insuf
			_noCoinsClock.restart();
		}
	}
	_currentMenu->hide();
}

//CLICKS EN EL MENU 2
void Level::clickWithMenu2Open(int mousex, int mousey, Spot& sp)
{
	Button* btn = _currentMenu->validateClickOnButton(mousex, mousey, sp);
	Tower* tower = sp.getCurrentTower();
	
	//se hizo click en el boton 1 que es UPGRADE
	if (btn->getBtnNumber() == 1) {  

		if (validateSale(tower, false)) { //validar si alcanza el dinero

			sell(tower, sp);
			tower->setSpotNumber(sp.getSpotNumber());
			tower->setOrigin(sp.getOrigin()); //nuevo
			setActiveTowers(tower);
			setSpot(&sp); 
			tower->upgrade();
		}
		else {
			_noCoinsClock.restart(); // reseteo el clock para que se muestre el cartel
		}
	}
	////se hizo click en el boton 2 que es REVENTA:
	else if (btn->getBtnNumber() == 2) { 
		tower->sayBye();
		resellTower(sp);
	}

	_currentMenu->hide();
}


void Level::validateClickOnSpeaker(int mousex, int mousey)
{
	if (_ui.getSpeaker().getGlobalBounds().contains(mousex, mousey))
	{
		if (_soundManager.getMusicOn())
		{
			_soundManager.setMusicOn(false);
			_soundManager.pauseMusic();
			_ui.setTextureSpeaker("img/complementarias/mute.png");
		}
		else
		{
			_soundManager.setMusicOn(true);
			_soundManager.playMusic();
			_ui.setTextureSpeaker("img/complementarias/musicOn.png");
		}
	}
}


//VOLVER AL HOME
void Level::validateClickOnHome(int mousex, int mousey, int& view)
{
	if (_ui.getText5().getGlobalBounds().contains(mousex, mousey))
	{
		_soundManager.stopMusic();
		MenuAbstract::getInstance().setNumberMenu(1);
		view = 1;
	}
}
