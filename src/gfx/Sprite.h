#pragma once

#include <cstdint>
#include <memory>

// every sprite will have a color palette of up to 4 different colors
// the palettes will work by storing the indices of the colors they want
// from the Renderer's colorPalette
class ColorPalette
{
private:
	static constexpr uint8_t NUM_COLORS{ 4 };

private:
	uint8_t colors[NUM_COLORS];

public:
	ColorPalette();
	ColorPalette(const uint8_t const colors[NUM_COLORS]);
	ColorPalette(const uint8_t ci1, const uint8_t ci2, const uint8_t ci3, const uint8_t ci4);

	void setColors(const uint8_t ci1, const uint8_t ci2, const uint8_t ci3, const uint8_t ci4);
	void setColor(const uint8_t ci, const uint8_t index);

	const uint8_t getNumColors() const;
	const uint8_t* getColors() const;
};

// ill have to remember this, but i guess I want it so when animations are implemented,
// that key frames are loaded in and out of memory on the spot?
class Sprite
{
private:
	ColorPalette palette;

	// first 4 bits represent the number of bytes needed for the width of the sprite
	// the leading 4 bits represent number of bytes needed for the height of the sprite
	// 
	// because we can store 4 pixels in 1 byte, the we can use 4 bits to represent nums 1-16
	// 1111 1111 value of dimensions would mean we have a 16x16 byte sprite
	// which would be 64x64 pixels
	uint8_t width;
	uint8_t height;
	// 1 byte of padding

	// since we only have 4 different colors in the color palette,
	// we can represent the index of color in our palette in just 2 bits
	// so in 1 byte, we will have 8 bits, which can represent 4 pixels of the sprite
	// this means the sprites dimensions will have to be in multiples of 4
	std::unique_ptr<uint8_t[]> data;

public:
	Sprite(const uint8_t width, const uint8_t height, const uint8_t* const data);
	// will need deep memcpy for color palette
	Sprite(const uint8_t width, const uint8_t height, const uint8_t* const data, const ColorPalette& cp);

	const uint8_t getWidth() const;
	const uint8_t getHeight() const;
	const uint8_t* const getData() const;

	// to interface with palette
	ColorPalette& getPalette();

};