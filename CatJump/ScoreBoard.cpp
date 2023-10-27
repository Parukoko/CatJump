#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {}

void ScoreBoard::AddName(Name& name) {
	names.push_back(name);
}

std::vector<Name>& ScoreBoard::GetName() {
	return names;
}