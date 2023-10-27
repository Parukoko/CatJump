#include "Menu.h"

Menu::Menu(float width, float height)
{
	this->font.loadFromFile("LongDrive.ttf");

	//Play button
	this->menuText[0].setFont(font);
	this->menuText[0].setFillColor(sf::Color::Red);
	this->menuText[0].setString("Play");
	this->menuText[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	//ScoreBoard
	this->menuText[1].setFont(font);
	this->menuText[1].setFillColor(sf::Color::White);
	this->menuText[1].setString("Score Board");
	this->menuText[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	//Exit
	this->menuText[2].setFont(font);
	this->menuText[2].setFillColor(sf::Color::White);
	this->menuText[2].setString("Exit");
	this->menuText[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	this->selectedItemIndex = 0;


}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
		window.draw(menuText[i]);
	}
}

void Menu::MoveDown()
{
	this->menuText[this->selectedItemIndex].setFillColor(sf::Color::White);
	this->selectedItemIndex++;
	this->menuText[this->selectedItemIndex % 3].setFillColor(sf::Color::Red);

}

void Menu::MoveUp()
{
	this->menuText[this->selectedItemIndex].setFillColor(sf::Color::White);
	this->selectedItemIndex--;
	this->menuText[this->selectedItemIndex % 3].setFillColor(sf::Color::Red);
}
