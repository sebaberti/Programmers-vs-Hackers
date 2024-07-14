#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _direction;

	int _type;
	int _damage;
	float _speed;
	sf::Vector2f _enemyPosition;

public:
	

	void moveToward();
	void loadTexture(std::string);

	int getDamage() const;
	int getType();

	sf::FloatRect getBounds() const;
	void update();
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	~Bullet() {};
};
