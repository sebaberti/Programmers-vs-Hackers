#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Bullet.h"
#include "HackerTrainee.h"

class Tower : public sf::Drawable, public sf::Transformable
{
protected:
	sf::CircleShape _visualRange;
	sf::Sprite _sprite;
	//Propiedades esteticas
	sf::Texture _texture;
	std::string _name;
	//Propiedades oro
	int _price;
	int _priceUpgrade;
	int _salesValue;

	//audios
	sf::SoundBuffer _bufferTeacher;
	sf::Sound _soundTeacher;

	//Propiedades belicas:
	int _damage;
	int _damageUpgrade;
	int _upgradesAmount;

	int _spotNumber;
	int _type; //new

	sf::Clock _clock;
	float _fireRate;
	float _fireRateUpgrade;
	Bullet* _bullet;

public:
	virtual Tower* clone() const = 0; // Método clone para crear nuevas instancias
	virtual void upgrade()=0;
	virtual void sayHi() = 0;
	virtual void sayBye() = 0;

	//Getters
	int getPrice() const;
	int getPriceUpgrade() const;
	int getSalesValue() const;
	int getDamage() const;
	int getDamageUpgrade() const;
	float getFireRate() const;
	float getFireRateUpgrade() const;
	int getUpgradesAmount() const;
	int getSpotNumber() const;
	Bullet* getBullet() const;
	int getType() const;

	void setSpotNumber(int);

	//Comportamiento
	sf::FloatRect getBounds() const;
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	bool canShoot();
};
