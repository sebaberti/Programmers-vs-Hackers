#include "Button.h"
#include "ButtonUpgrade.h"

ButtonUpgrade::ButtonUpgrade()
{
	_mouseHover = false;
	if (!_texture.loadFromFile("img/menuContextual/button_tower_updateMenu_attack.png"))
	{
		throw std::runtime_error("Error img Buttom Upgrade");
	}

	_sprite.setTexture(_texture);
	_sprite.setScale(0.7f, 0.7f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	setSpriteHover();


}
