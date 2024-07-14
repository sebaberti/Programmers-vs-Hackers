#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Map : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Sprite _sprite;
	sf::Texture _tileMap;
	std::list<sf::Sprite> _tiles;	

public:
	Map(std::string);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
};

