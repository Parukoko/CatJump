#include "Coin.h"

Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)
{
    body.setSize(sf::Vector2f(50.0f, 75.0f));
    body.setOrigin(body.getSize() / 2.0f);
    initialPosition = position;
    body.setPosition(position);
    body.setTexture(texture);
}

void Coin::Update(float deltaTime)
{
    animation.Update(0, deltaTime, true);
}

void Coin::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

