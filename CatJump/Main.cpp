#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Animation.h"
#include "Player.h"  
#include "Platform.h"
#include "Enemy.h"
#include "Coin.h"
#include "Timer.h"
#include "Menu.h"
#include "ScoreBoard.h"
#include "Name.h"
#include "Game.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

static const float VIEW_HEIGHT = 900.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = static_cast<float>(window.getSize().x) / window.getSize().y;
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

std::string InputPlayerName(sf::RenderWindow& window)
{
	std::string playerName;
	bool enteringName = true;
	sf::Event nameEntryEvent;
	while (window.isOpen() && enteringName) {
		while (window.pollEvent(nameEntryEvent)) {
			if (nameEntryEvent.type == sf::Event::TextEntered) {
				if (nameEntryEvent.text.unicode == '\b' && playerName.size() > 0) {
					playerName.pop_back();
				}
				else if (nameEntryEvent.text.unicode < 128) {
					playerName += static_cast<char>(nameEntryEvent.text.unicode);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				enteringName = false;
				sf::sleep(sf::milliseconds(200));
			}

			window.clear(sf::Color::Black);
			window.display();
		}
	}
	return playerName;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "CatJump", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("cat101.png");
	sf::Texture coinTexture;
	coinTexture.loadFromFile("coin10101.png");

	ScoreBoard Scoreboard;
	Name name;
	Name playerNameObject;
	Player player(&playerTexture, sf::Vector2u(4, 2), 0.5f, 100.0f, 250);

	const int numRandomPositions = 10;

	std::vector<Platform> platforms;
	std::vector<Enemy> enemies;
	std::vector<Coin> coins;
	std::vector<sf::Vector2f> randomCoinPositions;
	std::vector<Name> scoreboard;
	//std::vector<Name>& names = Scoreboard.GetName();
	std::vector<Coin> collectedCoins;

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (int i = 0; i < numRandomPositions; i++) {
		float randomX = static_cast<float>(std::rand() % window.getSize().x);
		float randomY = static_cast<float>(std::rand() % window.getSize().y);
		randomCoinPositions.push_back(sf::Vector2f(randomX, randomY));
	}


	for (const sf::Vector2f& position : randomCoinPositions) {
		coins.push_back(Coin(&coinTexture, sf::Vector2u(1, 1), 0.3f, position));
	}

	for (int i = 0; i < 9; i++) {
		float x = 50.0f + (300.0f * i);
		for (int j = 0; j < 3; j++) {
			if (i % 2 == 0) {
				float y = 150.0f + (300.0f * j);
				platforms.push_back(Platform(nullptr, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(x, y)));
			}
			if (i % 2 == 1) {
				float y = 0.0f + (300.0f * j);
				platforms.push_back(Platform(nullptr, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(x, y)));
			}
		}
	}

	platforms.push_back(Platform(nullptr, sf::Vector2f(2000.0f, 50.0f), sf::Vector2f(900.0f, 900.0f)));

	Timer gameTime;
	Timer survivalTime;

	float deltaTime = 0.0f;
	sf::Clock clock;
	float enemySpawnTimer = 0.0f;
	float enemySpawnInterval = 0.5f;

	Menu menu(window.getSize().x, window.getSize().y);

	sf::Vector2f direction;
	sf::Font font;
	sf::Text gameText;
	sf::Text survivalText;
	sf::Text ScoreboardText;
	std::string playerName;

	font.loadFromFile("LongDrive.ttf");

	sf::Text playerNameText;
	playerNameText.setFont(font);
	playerNameText.setCharacterSize(24);
	playerNameText.setFillColor(sf::Color::White);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2);

	sf::Text NameText;
	NameText.setFont(font);
	NameText.setCharacterSize(30);
	NameText.setFillColor(sf::Color::White);
	NameText.setString("Thanatchaya Toom-ariya 66010345");
	NameText.setPosition(window.getSize().x - 400, window.getSize().y - 50);

	bool nameEntered = false;
	bool enteringName = false;
	bool playing = false;
	bool gameOver = false;

	while (window.isOpen())
	{
		bool enterPressed = false;

		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					if (playing) enterPressed = true;
					playing = true;
					break;
				}
				break;
			case sf::Event::TextEntered:
				if (enteringName)
				{
					if (evnt.text.unicode == '\b' && playerName.size() > 0) {
						playerName.pop_back();
					}
					else if (evnt.text.unicode > 32 && evnt.text.unicode < 128) {
						playerName += static_cast<char>(evnt.text.unicode);
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			default:
				break;
			}
		}

		if (!playing) {
			menu.draw(window);
			window.draw(NameText);
		}

		if (playing) {
			switch (menu.GetPressedItem())
			{
			case 0: {
				view.setCenter(player.GetPosition());
				if (!nameEntered) enteringName = true;
				if (enteringName) {
					playerNameText.setString("Player Name: " + playerName);
					playerNameText.setPosition(window.getSize().x / 2, window.getSize().y / 2);
					playerNameText.setCharacterSize(40);
					if (enterPressed) {
						enteringName = false;
						nameEntered = true;
					}
					break;
				}
				enemySpawnTimer += deltaTime;
				player.Update(deltaTime);
				if (enemySpawnTimer >= enemySpawnInterval) {
					enemySpawnTimer = 0.0f;
					float enemyRadius = 10.0f + (rand() % 20);
					enemies.push_back(Enemy(enemyRadius, 1000.0f));
				}

				//platform
				for (Platform& platform : platforms) {
					if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
						player.OnCollision(direction);
					}
				}
				for (Platform& platform : platforms)
					platform.Draw(window);


				//enemy
				for (Enemy& enemy : enemies) {

					if (player.GetCollider().CheckIntersect(enemy.GetCollider(), direction, 0.0f) && !enemy.getHit()) {
						player.DecreaseHealth(1);
						enemy.kill();
					}

					if (!enemy.getHit()) {
						enemy.Update(deltaTime);
						enemy.Draw(window);
					}
				}

				//coin
				for (Coin& coin : coins) {
					coin.Draw(window);
				}

				coins.erase(std::remove_if(coins.begin(), coins.end(), [&player, &collectedCoins](Coin& coin) {
					if (coin.GetGlobalBounds().intersects(player.GetCollider().GetGlobalBounds())) {
						collectedCoins.push_back(coin);
						return true;
					}
					return false;
				}), coins.end());

				if (collectedCoins.size() == 10) {
					survivalTime.Stop();
					playing = false;
					enterPressed = true;
					Game::save_score(playerName, static_cast<int>(survivalTime.GetTotalTime()));
				}

				//Timer
				if (player.GetHealth() > 0) {
					survivalTime.Start();
				} 
				else {
					if (!gameOver) {
						gameOver = true;
						player.setPosition(sf::Vector2f(100.0f, 0.0f));
						survivalTime.Stop();
						for (int i = 0; i < numRandomPositions; i++) {
							float randomX = static_cast<float>(std::rand() % window.getSize().x);
							float randomY = static_cast<float>(std::rand() % window.getSize().y);
							randomCoinPositions.push_back(sf::Vector2f(randomX, randomY));
						}

						for (const sf::Vector2f& position : randomCoinPositions) {
							coins.push_back(Coin(&coinTexture, sf::Vector2u(1, 1), 0.3f, position));
						}
					}
					window.clear();
					for (Coin& coin : coins) {
						coin.Draw(window);
					}
					window.draw(gameOverText);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						player.reset();  
						survivalTime.Reset();
						collectedCoins.clear();
						gameOver = false;
					}
					for (Platform& platform : platforms)
						platform.Draw(window);

				}
				gameTime.Reset();
				gameTime.Start();
				player.Draw(window);

				gameText.setString("Health: " + std::to_string(static_cast<int>(player.GetHealth())));
				gameText.setPosition(50.0f, 50.0f);
				gameText.setFillColor(sf::Color::White);
				gameText.setFont(font);
				gameText.setCharacterSize(40);
				window.draw(gameText);

				survivalText.setString("Survival Time: " + std::to_string(static_cast<int>(survivalTime.GetTotalTime())));
				survivalText.setPosition(50.0f, 10.0f);
				survivalText.setFillColor(sf::Color::White);
				survivalText.setFont(font);
				survivalText.setCharacterSize(40);
				window.draw(survivalText);
				break;

			}
			case 1:
				Game::loadfile_andsort(&window);
				break;
			case 2:
				window.close();
				break;
			}
		}

		view.setCenter(player.GetPosition());


		if (enteringName) {
			window.draw(playerNameText);
		}

		window.display();
		window.clear();
	}

	return 0;
}