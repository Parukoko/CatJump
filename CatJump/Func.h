#pragma once
class Func {
private:
	sf::RenderWindow m_window;
	sf::Event m_event;
	   

	const float& m_fdt;
	const float& m_dt;

	sf::Vector2i m_windowOffset;
	bool m_windowGrabbed = false;

	void MoveWindow();

};

