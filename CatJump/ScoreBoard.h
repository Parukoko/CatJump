#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Name.h"

class ScoreBoard
{
public :
	ScoreBoard();

	void AddName(Name& name);
	std::vector<Name>& GetName();
private :
	std::vector<Name> names;
};
