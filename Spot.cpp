#include <iostream> //borrar
#include <SFML/Graphics.hpp>

#include "Spot.h"

Spot::Spot()
{
	_spotNumber = 0;
    _mouseHover = false;

	if (!_textureA.loadFromFile("img/maps/spot_martillo.png")) {
		throw std::runtime_error("Error img Torre Brian");
	}

	_spriteA.setTexture(_textureA);
	_spriteA.setOrigin(_spriteA.getGlobalBounds().width / 2, _spriteA.getGlobalBounds().height / 2);
	_spriteA.setScale(1.4f, 1.4f);
	if (!_textureB.loadFromFile("img/maps/spot_martillo_hover.png")) {
		throw std::runtime_error("Error img Torre Brian");
	}
	_spriteB.setTexture(_textureB);
	_spriteB.setOrigin(_spriteB.getGlobalBounds().width / 2, _spriteB.getGlobalBounds().height / 2);
	_spriteB.setScale(1.4f, 1.4f);
	_occupied = false;
}

int Spot::getSpotNumber() const { return _spotNumber; }
bool Spot::getIsOccupied() const { return _occupied; }
Tower* Spot::getCurrentTower() const { return _currentTower; }
bool Spot::getMouseHover() const { return _mouseHover; }

void Spot::setSpot(int spotNumber, bool status) {
	setSpotNumber(spotNumber);
	setOccupied(status);
}
void Spot::setSpotNumber(int n) { _spotNumber = n; }
void Spot::setMouseHover(bool state) { _mouseHover = state; }
void Spot::setOccupied(bool status){ _occupied = status; }
void Spot::setCurrentTower(Tower* tower) { _currentTower = tower; }

void Spot::mouseCheck(sf::Vector2f& transformedMousePos)
{
	if (getGlobalBounds().contains(transformedMousePos))
		setMouseHover(true);
	else
		setMouseHover(false);
}

void Spot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	//ocupado -> dibuja la torre
	if (getIsOccupied())
	{
		target.draw(*_currentTower, states);
	}
	//si no verifica para hacer el hover
	else {
		_mouseHover ? target.draw(_spriteB, states) : target.draw(_spriteA, states);
	}
}


sf::FloatRect Spot::getGlobalBounds() const {
	return getTransform().transformRect(_spriteA.getGlobalBounds());
}

void Spot::clearCurrentTower()
{
	_currentTower = nullptr;
}


Spot::~Spot()
{
	if (_currentTower != nullptr)
		_currentTower = nullptr;
}