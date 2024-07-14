#include "FileLevel.h"
#include "MenuAbstract.h"
#include "MenuHome.h"

MenuHome::MenuHome(bool state)
{
	_soundManager.loadMusic("music/menuMusic.wav");
	_soundManager.setVolume(5);

	if (_soundManager.getMusicOn())
	{
		_soundManager.playMusic();
	}
	else {
		_soundManager.pauseMusic();
	}

	//texto
	for (int i = 0; i < 5; i++) {
		_text[i].setFont(_font);
		_text[i].setCharacterSize(30);
		int posY;
		std::string texto;
		switch (i)
		{
		case 0:
			posY = 100;
			texto = "Continue Game";
			break;
		case 1:
			posY = 200;
			texto = "Restart Game";
			break;
		case 2:
			posY = 300;
			texto = "Info";
			break;
		case 3:
			posY = 400;
			texto = "Pause music";
			break;
		case 4:
			posY = 500;
			texto = "Exit";
			break;
		default:
			break;
		}
		_text[i].setPosition(250, posY);
		_text[i].setString(texto);
		_text[i].setOrigin(_text[i].getGlobalBounds().getPosition().x / 2, _text[i].getGlobalBounds().height / 2);
		_text[i].setFillColor(sf::Color(255, 255, 255));
	}
}

bool MenuHome::getMusicPlaying() const { return _musicPlaying; }

void MenuHome::setSoundText(bool play)
{
	if(play)
	{
		_text[3].setString("Pause music");
	}
	else
	{
		_sound.pause();
		_text[3].setString("Play music");
	}
}


//Verificamos el click del mouse para las distintas acciones 
void MenuHome::validateClick(int mousex, int mousey, sf::RenderWindow& window, int& view)
{
	//Opción para jugar.
	if (getText1().getGlobalBounds().contains(mousex, mousey))
	{
		MenuAbstract::getInstance().setNumberMenu(2);
	}

	//Resetear los niveles.
	else if (getText2().getGlobalBounds().contains(mousex, mousey))
	{
		FileLevels arc;
		arc.reset();
		MenuAbstract::getInstance().setNumberMenu(2);
	}

	else if (getText3().getGlobalBounds().contains(mousex, mousey)) {
		MenuAbstract::getInstance().setNumberMenu(3);
	}

	//Activar desactivar Sonido.
	else if (getText4().getGlobalBounds().contains(mousex, mousey))
	{
		if (_soundManager.getMusicOn()) {
			setSoundText(false);
			_soundManager.setMusicOn(false);
			_soundManager.pauseMusic();
		}
		else
		{
			setSoundText(true);
			_soundManager.setMusicOn(true);
			_soundManager.playMusic();
		}
	}
	//Exit
	else if (getText5().getGlobalBounds().contains(mousex, mousey))
	{
		window.close();
	}
}


void MenuHome::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	Menu::draw(target, states);
	for (int i = 0; i < 5; i++) {
		target.draw(_text[i], states);
	}
}