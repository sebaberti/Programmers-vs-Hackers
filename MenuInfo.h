#pragma once
class MenuInfo : public Menu
{
private:
	sf::Texture _textureInfo;
	sf::RectangleShape _info;

public:
	MenuInfo(bool);
	void validateClick(int, int, sf::RenderWindow&, int&) override;
	void draw(sf::RenderTarget&, sf::RenderStates) const;
};

