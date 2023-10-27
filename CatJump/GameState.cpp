#include "GameState.h"

GameState::GameState(sf::RenderWindow& window, ScoreBoard& scoreBoard)
    : window(window), scoreBoard(scoreBoard) {}

void GameState::handleEvents(sf::Event& event) {
    // Default implementation for handling events, you can override in derived classes
}

void GameState::update(float deltaTime) {
    // Default implementation for updating game logic, you can override in derived classes
}

void GameState::render() {
    // Default implementation for rendering, you can override in derived classes
}

MenuState::MenuState(sf::RenderWindow& window, ScoreBoard& scoreBoard, Menu& menu)
    : GameState(window, scoreBoard), menu(menu) {}

void MenuState::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            menu.MoveUp();
            break;
        case sf::Keyboard::Down:
            menu.MoveDown();
            break;
        case sf::Keyboard::Return:
            switch (menu.GetPressedItem()) {
                // Handle menu item selections
            }
            break;
        }
    }
}

void MenuState::update(float deltaTime) {
    // Update menu state logic
}

void MenuState::render() {
    // Render menu state
}

PlayState::PlayState(sf::RenderWindow& window, ScoreBoard& scoreBoard, Player& player, std::vector<Platform>& platforms, std::vector<Enemy>& enemies, std::vector<Coin>& coins, Timer& gameTime, Timer& survivalTime)
    : GameState(window, scoreBoard), player(player), platforms(platforms), enemies(enemies), coins(coins), gameTime(gameTime), survivalTime(survivalTime) {}

void PlayState::handleEvents(sf::Event& event) {
    // Handle events specific to the play state
    // Handle player input, collisions, and other gameplay events
}

void PlayState::update(float deltaTime) {
    // Update gameplay state, including player, platforms, enemies, coins, timers, etc.
}

void PlayState::render() {
    // Render gameplay state
    // Render player, platforms, enemies, coins, timers, HUD, etc.
}
