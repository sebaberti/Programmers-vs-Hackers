#include <SFML/Graphics.hpp>
#include "Button.h"


//Retorna un puntero a la torre  asociada al botón.
Tower* Button::getTower() const { return _tower; }

int Button::getPrice() const {
	if (_tower != nullptr)
		return _tower->getPrice();
	else return _price;
}

int Button::getDamage() const {
	if (_tower != nullptr)
		return _tower->getDamage();
	else return _damage;
}

std::string Button::getFireRateText() const {
	float fireRt;
	if (_tower != nullptr)
		fireRt = _tower->getFireRate();
	else fireRt = _fireRate;

	if (fireRt <= 0.8f) {
		return "Fastest";
	}
	else if (fireRt <= 1.1f) {
		return "Fast";
	}
	else if (fireRt <= 1.5f) {
		return "Normal";
	}
	else if (fireRt <= 1.7f) {
		return "Slow";
	}
	else return "Slowest";
}

int Button::getBtnNumber() const { return _btnNumber; }
void Button::setMouseHover(bool state) { _mouseHover = state; }


//hover de los botones
void Button::setSpriteHover()
{
	if (!_textureHover.loadFromFile("img/menuContextual/button_tower_menu_hover.png"))
	{
		throw std::runtime_error("Error img button Hover");
	}
	_spriteHover.setTexture(_textureHover);
	_spriteHover.setScale(0.7f, 0.7f);
	_spriteHover.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

void Button::setBtnNumber(int n) { _btnNumber = n; }


//imagen y precio 
void Button::setPriceText()
{
	if (!_textureBgPrice.loadFromFile("img/menuContextual/priceBg.png")) {
		throw std::runtime_error("Error al cargar img bckground de Precio");
	}
	_spriteBgPrice.setTexture(_textureBgPrice);
	_spriteBgPrice.setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
	_spriteBgPrice.setPosition(0, -50);

	if (!_fontPriceTx.loadFromFile("fuentes/TowerPrice.ttf")) {
		throw std::runtime_error("Error al cargar la fuente del Price Menu \n");
	}
	_priceText.setFont(_fontPriceTx);
	_priceText.setCharacterSize(28);
	_priceText.setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
	_priceText.setPosition(5, -54);
	_priceText.setFillColor(sf::Color(255, 255, 255));
	_priceText.setString("$" + std::to_string(getPrice()));
}

void Button::setPrice(int price) { _price = price; }
void Button::setDamage(int damage) { _damage = damage; }
void Button::setFireRate(float fireRate) { _fireRate = fireRate; }


void Button::setInfo()
{
	if (!_textureBgInfo.loadFromFile("img/menuContextual/priceBg.png")) {
		throw std::runtime_error("Error al cargar Background de Info/precio");
	}
	_spriteBgInfo.setTexture(_textureBgInfo);
	_spriteBgInfo.setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
	_spriteBgInfo.setPosition(-10, 80);
	_spriteBgInfo.setScale(1.5, 1.5);

	if (!_textureSword.loadFromFile("img/menuContextual/sword.png")) {
		throw std::runtime_error("Error al cargar img espadita");
	}
	_spriteSword.setTexture(_textureSword);
	_spriteSword.setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
	_spriteSword.setPosition(-15, 80);

	if (!_textureHourGlass.loadFromFile("img/menuContextual/hourGlass.png")) { 
		throw std::runtime_error("Error al cargar img reloj de arena");
	}
	_spriteHourGlass.setTexture(_textureHourGlass);
	_spriteHourGlass.setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
	_spriteHourGlass.setPosition(-15, 100);

	if (!_fontInfo.loadFromFile("fuentes/futura.ttf")) {
		throw std::runtime_error("Error al cargar la fuente del Info Menu \n");
	}

	for (int i = 0; i < 2; i++) {
		_info[i].setFont(_fontInfo);
		_info[i].setCharacterSize(20);
		_info[i].setOrigin(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height / 2);
		_info[i].setFillColor(sf::Color(255, 255, 255));
	}

	_info[0].setPosition(15, 75);
	_info[0].setString(std::to_string(getDamage()));
	_info[1].setPosition(10, 100);
	_info[1].setString(getFireRateText());
}

void Button::update(sf::Vector2i& mousePosition)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
	target.draw(_spriteBgPrice, states);
	target.draw(_priceText, states);
	if (_mouseHover) {
		target.draw(_spriteBgInfo, states);
		target.draw(_spriteHover, states);
		target.draw(_spriteSword, states);
		target.draw(_spriteHourGlass, states);
		target.draw(_info[0], states);
		target.draw(_info[1], states);
	}

}

sf::FloatRect Button::getGlobalBounds() const {
	return getTransform().transformRect(_sprite.getGlobalBounds());
}
