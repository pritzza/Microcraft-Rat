#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdint>

class Window
{
private:
	sf::RenderWindow window;
		
	// render() method will take in the rendered scene, and every frame
	// the window will need to turn it into a texture which needs
	// to be applied to a sprite object before it can be drawn
	sf::Texture textureBuffer;
	sf::Sprite spriteBuffer;

	const uint16_t width;
	const uint16_t height;

	bool focused{ true };

private:
	void pollEvents();

public:
	Window(const uint16_t width, const uint16_t height, const std::string& name, const int style);

	void update();
	void render(const sf::Image& buffer);	// maybe just store a pointer or ref of buffer

	inline const uint16_t getWidth() const		{ return this->width;   }
	inline const uint16_t getHeight() const		{ return this->height;  }
	inline const sf::Window& getWindow() const  { return this->window;  }

	inline const bool isFocused() const			{ return this->focused; }
	inline const bool isOpen() const			{ return this->window.isOpen(); }
};