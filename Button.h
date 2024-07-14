#pragma once
#include "Tower.h"
class Button : public sf::Drawable, public sf::Transformable
{
protected:
	Tower* _tower;
	int _price;
	int _damage;
	float _fireRate;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Texture _textureHover;
	sf::Sprite _spriteHover;
	bool _mouseHover;
	int _btnNumber;
	sf::Font _fontPriceTx;
	sf::Font _fontInfo;
	sf::Text _priceText;
	sf::Texture _textureBgPrice;
	sf::Sprite _spriteBgPrice;
	sf::Text _info[4];
	sf::Texture _textureBgInfo;
	sf::Sprite _spriteBgInfo;
	sf::Texture _textureSword;
	sf::Sprite _spriteSword;
	sf::Texture _textureHourGlass;
	sf::Sprite _spriteHourGlass;

public:
	Tower* getTower() const; // Devuelve una nueva instancia
	int getPrice() const;
	int getDamage() const;
	std::string getFireRateText() const;
	int getBtnNumber() const;
	
	void setMouseHover(bool);
	void setSpriteHover();
	void setBtnNumber(int);
	void setPriceText();	
	void setPrice(int);
	void setDamage(int);
	void setFireRate(float);
	void setInfo();

	void update(sf::Vector2i&);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::FloatRect getGlobalBounds() const;
};
