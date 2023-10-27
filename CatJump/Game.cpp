
#include "Game.h"

bool Game::compareScores(const ScoreEntry& a, const ScoreEntry& b)
{
    return a.score > b.score;
}

void Game::loadfile_andsort(int scorePlay) {
    std::ifstream inputFile("point.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    std::vector<ScoreEntry> scoreEntries;
    std::string name;

    while (inputFile >> name >> scorePlay) {
        ScoreEntry entry;
        entry.name = name;
        entry.score = scorePlay;
        scoreEntries.push_back(entry);
    }

    inputFile.close();

    std::sort(scoreEntries.begin(), scoreEntries.end(), compareScores);

    const int numTopScores = 5;
    std::string topNames[numTopScores];
    int topScores[numTopScores];

    std::cout << "Top 5 Scores:\n";
    for (int i = 0; i < numTopScores && i < scoreEntries.size(); ++i) {
        topNames[i] = scoreEntries[i].name;
        topScores[i] = scoreEntries[i].score;
        std::cout << topNames[i] << ": " << topScores[i] << std::endl;
    }

    sf::Text top5[numTopScores];
    sf::Text name5[numTopScores];

    for (int i = 0; i < numTopScores && i < scoreEntries.size(); ++i) {
        sf::Font font;
        top5[i].setFont(font); // Use the appropriate font
        top5[i].setFillColor(sf::Color(140, 109, 76));
        top5[i].setString(topNames[i]);
        top5[i].setPosition(65, 590 + (50 * i));

        sf::Text scoreText;
        scoreText.setFont(font); // Use the appropriate font
        scoreText.setFillColor(sf::Color(140, 109, 76));
        scoreText.setString(std::to_string(topScores[i])); // Convert int to string
        scoreText.setPosition(335, 590 + (50 * i));
        name5[i] = scoreText;
    }
}
