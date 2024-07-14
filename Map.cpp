#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <iostream>

#include "Map.h"

Map::Map(std::string file) {
	if (!_tileMap.loadFromFile(file)) {
		throw std::runtime_error("Error al cargar la textura del tilest");
	}

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 30; x++) {
			_sprite.setTexture(_tileMap);
			_sprite.setTextureRect(sf::IntRect(x * 32, y * 32, 32, 32));
			_sprite.setPosition(32 * x, 32 * y);
			_tiles.push_back(_sprite);
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	states.transform *= getTransform();
	for (const auto& tile : _tiles) {
		target.draw(tile, states);
	}
}