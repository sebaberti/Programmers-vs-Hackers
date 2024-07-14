#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "SoundManager.h"

class Menu :  public sf::Drawable
{
protected:
	sf::Texture _textureBanner;
	sf::RectangleShape _banner;
	sf::Font _font;
	sf::Text _text[6]; 
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	bool _musicPlaying;

	SoundManager& _soundManager;

public:
	Menu();
	virtual void validateClick(int, int, sf::RenderWindow&, int&)=0;
	void mouseCheck(sf::Vector2i&);
	sf::Text getText1() const;
	sf::Text getText2() const;
	sf::Text getText3() const;
	sf::Text getText4() const;
	sf::Text getText5() const;
	sf::Text getText6() const;

	bool getMusicPlaying() const;
	float getSoundPosition() const;

	void setMusicPlaying(bool);
	void setSound(bool);
	void setSoundPosition(float);

	void update(sf::Vector2i&);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	~Menu();
};
