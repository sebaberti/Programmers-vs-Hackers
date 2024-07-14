#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "MenuAbstract.h"
#include "FileLevel.h"
#include "Manager.h"
#include "SoundManager.h"

int main()
{
	FileLevels arc;
	Levels reg;
	

	//MUESTRO COMO ESTA ACTUALMENTE EL ARCHIVO:
	for (int i = 0; i < 5; i++) {
		reg = arc.read(i);
		reg.Mostrar();
	}

	sf::RenderWindow window(sf::VideoMode(960, 640), "Programmers Vs Hackers");
	window.setFramerateLimit(60);

	sf::Image icon;
	if (!icon.loadFromFile("img/complementarias/logo.png")) {
		throw std::runtime_error("Error al cargar logo miniatura");
	}

	//utiliza el tamaño y el puntero a los píxeles de esta imagen para 
	//establecerla como el icono de la ventana 
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	int view = 1;

	sf::Vector2i mousePosition; 

	//BUCLE PRINCIPAL
	while (window.isOpen())
	{
		//patron singleton para obtener la instancia, y gestionar los sonidos
		SoundManager& soundManager = SoundManager::getInstance();

		mousePosition = sf::Mouse::getPosition(window);

		//BUCLE PARA MANEJAR EVENTOS
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			
		
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
			{
				//obtengo las coordenas del click
				int mousex = ev.mouseButton.x;
				int mousey = ev.mouseButton.y;

				switch (view)
				{
				case 1:
				{
					MenuAbstract& menu = MenuAbstract::getInstance();
					menu.validateClick(mousex, mousey, window, view);
				}
				break;
				case 2:
				{
					Manager& mg = Manager::getInstance();
					mg.validateClick(mousex, mousey, window, view);
				}
				break;
				}
				
			}
			
		}
		

			window.clear();//borra el contenido de la ventana para el proximo render

			switch (view)
			{
			case 1:
			{
				MenuAbstract& menu = MenuAbstract::getInstance();
				menu.update(mousePosition);
				window.draw(menu);
			}
			break;
			case 2:
			{
				Manager& mg = Manager::getInstance();
				mg.update(mousePosition, view);
				window.draw(mg);
			}
			break;
			}
		
		//muestra el contenido dibujado

		window.display();
		if (ev.type == sf::Event::EventType::Closed) {
			window.close();
		}

		if (ev.key.code == sf::Keyboard::Key::Escape)
			window.close();

	}
	return 0;
}