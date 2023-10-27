#include "Func.h"
#include <SFML/Graphics.hpp>
#include "Global.h"

void Func::MoveWindow() {
    const sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    const int offset = 30;

    if (m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::Left) {
        if (mousePos.x > 0 && mousePos.x < offset ||
            mousePos.x > WINDOW_WIDTH - offset && mousePos.x < WINDOW_WIDTH ||
            mousePos.y > 0 && mousePos.y < offset ||
            mousePos.y > WINDOW_HEIGHT - offset && mousePos.y < WINDOW_HEIGHT)
        {
            m_windowOffset = m_window.getPosition() - sf::Mouse::getPosition();
            m_windowGrabbed = true;
        }
    }
    else if (m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left) {
        m_windowGrabbed = false;
    }
    else if (m_event.type == sf::Event::MouseMoved && m_windowGrabbed) {
        m_window.setPosition(sf::Mouse::getPosition() + m_windowOffset);
    }
}