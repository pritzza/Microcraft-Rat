#include "Window.h"

#include <SFML/Window.hpp>

Window::Window(const uint16_t width, const uint16_t height, const std::string& name, const int style)
    :
    window{ sf::VideoMode(width, height, 16), name, sf::Style::Default | sf::Style::Resize },
    width{ width },
    height{ height }
{
	// put the texture in the sprite
	this->spriteBuffer.setTexture(textureBuffer);
	this->spriteBuffer.setTextureRect(sf::IntRect(0, 0, this->width, this->height)); 
}

void Window::pollEvents()
{
	sf::Event event;

	if (this->window.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			this->window.close();		break;
		case sf::Event::GainedFocus:	this->focused = true;		break;
		case sf::Event::LostFocus:		this->focused = false;		break;
		}
}

void Window::update()
{
	this->pollEvents();
}

void Window::render(const sf::Image& buffer)
{
	static const sf::Color CLEAR_COLOR{ 255, 0, 255 };

	// clear prev frame
	this->window.clear(CLEAR_COLOR);

	// put the buffer in the texture
	this->textureBuffer.loadFromImage(buffer);

	// put the sprite on the screen
	this->window.draw(this->spriteBuffer);

	// put window's buffer on computer screen
	this->window.display();
}