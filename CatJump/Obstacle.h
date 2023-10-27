#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Obstacle
{
public :
	Obstacle(sf::Texture* texture);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
private :
	sf::RectangleShape body;
	void add(sf::Vector2f Velocity);

	Player player;
	sf::Clock clock;
	sf::Clock spawnClock;
};

