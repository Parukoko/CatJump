#pragma once
#include <string>
class Name
{
public :
	Name();
	Name(std::string& name, int score);

	std::string& GetName();
	int GetScore();

	void SetName(const std::string& name);
	void SetScore(int score);
private :
	std::string name;
	int score;
};

