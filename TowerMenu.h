#pragma once
#include "Spot.h"
#include "Button.h"
class TowerMenu : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	bool _isVisible;
	std::vector <Button*> _buttons;
	Spot* _currentSpot;
	int _NumberMenu;
public:
	virtual void setCurrentTower(Tower*)=0;

	bool getIsVisible();
	Button* getButtonByIndex(int) const;
	Spot* getCurrentSpot() const;
	int getNumberMenu() const;
	void setCurrentSpot(Spot*);
	void setButton(bool, int);

	void hide();
	void show();

	void mouseCheck(sf::Vector2i&);
	Button* validateClickOnButton(int, int, Spot&);
	void update(sf::Vector2i&);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::FloatRect getGlobalBounds() const;

};
