#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Hacker :public sf::Drawable, public sf::Transformable
{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _velocity;
	sf::Vector2f _direction;

	//audios
	sf::SoundBuffer _bufferHacker;
	sf::Sound _soundHacker;

	int _life;
	int _type;
	bool _isABoss;
	int _goldenDrop;
	sf::Vector2f _position;
	bool _reachedEnd; // llego al final del camino ?

	bool _isFreezed;

	//Animacion
	float _frame;
	sf::Vector2f _currentPosition;
	sf::Vector2f _previousPosition;

public:
	virtual int attackUtn() = 0;
	virtual void saySth() = 0;
	int getLife() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getDirection() const;
	bool getBoss() const;
	int getGoldenDrop() const;
	bool getEnd() const;

	void setEnd(bool);
	void setLife(int);
	void setVelocity(sf::Vector2f);
	void setDirection(sf::Vector2f);
	void setBoos(bool);
	void setGoldenDrop(int);

	//Comportamiento
	virtual void moveHacker(int arr[][30]);
	sf::FloatRect getBounds() const;
	void update(int arr[][30]);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	virtual void getFreezed();

	virtual void takeDamage(int,int);

	virtual void animation(float);
};
