#pragma once
#include "Menu.h"
class MenuAbstract : public sf::Drawable
{
private:
	MenuAbstract(int idMenu = 1); //constrcutor privado para Singleton
	static MenuAbstract* _currentInstance; ////puntero static que apunta
	// a la uinica instancia Singleton
	Menu* _currentMenu; 
	
public:
	//devuelve la referencia a la unica instancia del menu 
	static MenuAbstract& getInstance(); //para obtener la inst. Singleton
	void setNumberMenu(int);
	void validateClick(int, int, sf::RenderWindow&, int&);

	void update(sf::Vector2i&);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	~MenuAbstract();
};