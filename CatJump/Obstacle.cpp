#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture* texture) :
	body(body)
{
}
void Obstacle::add(sf::Vector2f Velocity)
{
	float multi = clock.getElapsedTime().asSeconds();
	Obstacle obstacle(500 + multi * 10);
	obstacle.GetPosition(Velocity);

}
void Obstacle::Update(float deltaTime)
{

}

void Obstacle::Draw(sf::RenderWindow& window)
{

}


