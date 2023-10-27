#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Coin.h"
#include "Timer.h"
#include "ScoreBoard.h"
#include "Name.h"
#include "Menu.h"

class GameState {
public:
    GameState(sf::RenderWindow& window, ScoreBoard& scoreBoard);
    virtual ~GameState() {}

    virtual void handleEvents(sf::Event& event);
    virtual void update(float deltaTime);
    virtual void render();

protected:
    sf::RenderWindow& window;
    ScoreBoard& scoreBoard;
};

class MenuState : public GameState {
public:
    MenuState(sf::RenderWindow& window, ScoreBoard& scoreBoard, Menu& menu);

    void handleEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render() override;

private:
    Menu& menu;
};

class PlayState : public GameState {
public:
    PlayState(sf::RenderWindow& window, ScoreBoard& scoreBoard, Player& player, std::vector<Platform>& platforms, std::vector<Enemy>& enemies, std::vector<Coin>& coins, Timer& gameTime, Timer& survivalTime);

    void handleEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render() override;

private:
    Player& player;
    std::vector<Platform>& platforms;
    std::vector<Enemy>& enemies;
    std::vector<Coin>& coins;
    Timer& gameTime;
    Timer& survivalTime;
    // Add other necessary game objects here
};

#endif // GAME_STATE_H
