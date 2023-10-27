#include "Enemy.h"
#include "Collider.h"

Enemy::Enemy(float radius, float speed) {
    this->hit = false;
    this->speed = speed;
    isMovingRight = (rand() % 2) == 1;
    body.setSize(sf::Vector2f(20.f, 20.f));
    body.setFillColor(sf::Color::Red);

    if (isMovingRight) {
        body.setPosition(0.0f, rand() % 1500);
        velocity.x = speed;
    }
    else {
        body.setPosition(1600.0f, rand() % 1500);
        velocity.x = -speed;
    }
}

void Enemy::kill(){
    this->hit = true;
}
bool Enemy::getHit() {
    return this->hit;
}
void Enemy::Update(float deltaTime) {
    body.move(velocity * deltaTime);
}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(body);
}
