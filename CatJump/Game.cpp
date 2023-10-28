
#include "Game.h"

bool Game::compareScores(const ScoreEntry& a, const ScoreEntry& b)
{
    return a.score > b.score;
}

void Game::save_score(std::string& playerName, int scorePlay) {
    std::ofstream outputFile("point.txt", std::ios::app);
    outputFile << playerName << ' ' << scorePlay;
    outputFile.close();
}

void Game::loadfile_andsort(sf::RenderWindow* window) {
    std::ifstream inputFile("point.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    std::vector<ScoreEntry> scoreEntries;
    std::string name;

    std::string playerName;
    int scorePlay;

    while (inputFile >> playerName >> scorePlay) {
        ScoreEntry entry;
        entry.name = playerName;
        entry.score = scorePlay;
        scoreEntries.push_back(entry);
    }

    inputFile.close();

    std::sort(scoreEntries.begin(), scoreEntries.end(), compareScores);

    const int numTopScores = 5;
    std::string topNames[numTopScores];
    int topScores[numTopScores];

    std::cout << "Top 5 Scores: \n";
    for (int i = 0; i < numTopScores && i < scoreEntries.size(); ++i) {
        topNames[i] = scoreEntries[i].name;
        topScores[i] = scoreEntries[i].score;
        std::cout << topNames[i] << ": " << topScores[i] << std::endl;
    }

    sf::Text top5[numTopScores];
    sf::Text name5[numTopScores];

    sf::Font font;
    font.loadFromFile("LongDrive.ttf");

    for (int i = 0; i < numTopScores && i < scoreEntries.size(); ++i) {
        top5[i].setFont(font);
        top5[i].setFillColor(sf::Color(140, 109, 76));
        top5[i].setString(topNames[i]);
        top5[i].setPosition(65, 590 + (50 * i));
        window->draw(top5[i]);

        name5[i].setFont(font); // Use the appropriate font
        name5[i].setFillColor(sf::Color(140, 109, 76));
        name5[i].setString(std::to_string(topScores[i]));
        name5[i].setPosition(335, 590 + (50 * i));
        window->draw(name5[i]);
    }
}
