#pragma once
class crouchingAnimation
{
	crouchingAnimation();
public :
	void Update(int row, float deltaTime, bool faceRight);
	sf::IntRect uvRect;
};

