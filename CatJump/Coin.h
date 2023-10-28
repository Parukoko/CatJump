#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Coin
{
public:
    Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    static Coin coinarr[36];
    void ResetPosition(sf::Vector2f(initialPosition)) {
        body.setPosition(initialPosition);
    }
private:
    Animation animation;
    sf::RectangleShape body;
    sf::Vector2f initialPosition;
};

