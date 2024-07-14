#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Spot.h"
#include "Button.h"
#include "ButtonBrian.h"
#include "TowerMenu.h"


bool TowerMenu::getIsVisible() { return _isVisible; }
Button* TowerMenu::getButtonByIndex(int i) const { return _buttons[i]; }
Spot* TowerMenu::getCurrentSpot() const { return _currentSpot; }
int TowerMenu::getNumberMenu() const { return _NumberMenu; }
void TowerMenu::setCurrentSpot(Spot* sp) { _currentSpot = sp; }
void TowerMenu::setButton(bool states, int i) { _buttons[i]->setMouseHover(states); }

void TowerMenu::hide() { _isVisible = false; }
void TowerMenu::show() { _isVisible = true; }


//si el mouse esta en algun boton para activar el hover
void TowerMenu::mouseCheck(sf::Vector2i& mousePosition)
{
	sf::Vector2f transformedMousePos = getInverseTransform().transformPoint(sf::Vector2f(mousePosition));
	for (auto& button : _buttons)
	{
		if (button->getGlobalBounds().contains(transformedMousePos))
		{
			button->setMouseHover(true);
		}
		else
		{
			button->setMouseHover(false);
		}
	}
}

Button* TowerMenu::validateClickOnButton(int mousex, int mousey, Spot& spot) { 
	sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(mousex), static_cast<float>(mousey));

	sf::Vector2f transformedMousePos = getInverseTransform().transformPoint(mousePos);
	for (Button* button : _buttons) { 
		if (button->getGlobalBounds().contains(transformedMousePos)) {
			return button;
		}
	}
	Button* btn = new ButtonBrian();
	btn->setBtnNumber(-1);
	return btn;
}

void TowerMenu::update(sf::Vector2i& mousePosition) {
	if (getIsVisible()) {
		for (Button* button : _buttons)
		{
			button->update(mousePosition);;
		}
	}
}

void TowerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
	for (Button* button : _buttons)
	{
		target.draw(*button, states);
	}
}

sf::FloatRect TowerMenu::getGlobalBounds() const {
	return getTransform().transformRect(_sprite.getGlobalBounds());
}


