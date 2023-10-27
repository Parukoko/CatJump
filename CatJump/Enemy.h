#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Enemy {
public:
    Enemy(float radius, float speed);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    Collider GetCollider() { return Collider(body); }
    bool getHit();
    void kill();
private:
    sf::RectangleShape body;
    float speed;
    bool isMovingRight;
    bool hit;

    sf::Vector2f velocity;
};
