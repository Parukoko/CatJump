// Game.h
#include <fstream>
#include <iostream>
#include <vector>d
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>

// Define the ScoreEntry structure if not already defined in Game.h
struct ScoreEntry {
    std::string name;
    int score;
};

class Game {
public:
    static bool compareScores(const ScoreEntry& a, const ScoreEntry& b);

    static void loadfile_andsort(std::string& playerName, int scorePlay);
};
