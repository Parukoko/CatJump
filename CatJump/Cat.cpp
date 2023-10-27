#include "Cat.h"

Cat::Cat()
{

	m_Speed = 400;


	m_Texture.loadFromFile("cat.png");
	m_Sprite.setTexture(m_Texture);


	m_Position.x = 500;
	m_Position.y = 800;

}


Sprite Cat::getSprite()
{
	return m_Sprite;
}

void Cat::moveLeft()
{
	m_LeftPressed = true;
}

void Cat::moveRight()
{
	m_RightPressed = true;
}

void Cat::stopLeft()
{
	m_LeftPressed = false;
}

void Cat::stopRight()
{
	m_RightPressed = false;
}


void Cat::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

}