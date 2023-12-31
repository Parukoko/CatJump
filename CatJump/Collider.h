#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void Move(float dx, float dy) { body.move(dx, dy); }
	bool CheckCollision(Collider other, sf::Vector2f& direction, float push);
	bool CheckIntersect(Collider other, sf::Vector2f& direction, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }

private:
	sf::RectangleShape& body;
};