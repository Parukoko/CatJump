#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
	const Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }

private:
	sf::RectangleShape body;
};