#include "Keyboard.h"

#include <SFML/Window.hpp>

Keyboard::Keyboard(const sf::RenderWindow& window)
	:
	window{ window }
{}

void Keyboard::update()
{
	w.update(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	a.update(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
	s.update(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	d.update(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
	e.update(sf::Keyboard::isKeyPressed(sf::Keyboard::E));
	space.update(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}