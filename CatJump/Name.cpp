#include "Name.h"

Name::Name() : name(""), score(0) {}

Name::Name(std::string& name, int score) : name(name), score(score) {}

std::string& Name::GetName()
{
	return name;
}

int Name::GetScore()
{
	return score;
}

void Name::SetName(const std::string& name)
{
	this->name = name;
}

void Name::SetScore(int score)
{
	this->score = score;
}
