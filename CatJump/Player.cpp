#include "Player.h"
#include "Animation.h"
#include "Collider.h"
#include "crouchingAnimation.h"
#include <SFML/Graphics.hpp>


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime){
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->row = 0;
	this->faceRight = true;
	this->canJump = true;
	this->health = 5;

	body.setSize(sf::Vector2f(100.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(450.0f, 200.0f);
	body.setTexture(texture);
}

void Player::Update(float deltaTime)
{
	Velocity.x *= 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && body.getPosition().x > 0 )
		Velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && body.getPosition().x < 1600)
		Velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		body.setSize(sf::Vector2f(75.0f, 30.0f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump && body.getPosition().y > 0)
	{
		canJump = false;
		Velocity.y = -sqrt(2.0f * 981.f * jumpHeight);
	}
	else {
		body.setSize(sf::Vector2f(75.0f, 75.0f));
	}


	Velocity.y += 981.f * deltaTime;

	if (Velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (Velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(Velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left
		Velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		Velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		Velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		Velocity.y = 0.0f;
	}
}

void Player::DecreaseHealth(int amount)
{
	health -= amount;
	if (health < 0) {
		health = 0;
	}
}

int Player::GetHealth(){
	return this->health;
}
