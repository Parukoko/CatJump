#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Text
{
public :
	Text();

	void setFont(sf::Font& font, unsigned int size);
	void setCharSize(unsigned int size);
	void reposition();
	void setSmooth(bool x);
	unsigned int GetSize() { return text.getCharacterSize(); }
	sf::Vector2f GetPosition() { return text.getPosition(); }
private :
	sf::Text text;

};

