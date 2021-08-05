#pragma once

#include <cstdint>

#include "../sprite/SpriteSheet.h"

class Renderer;

// every sprite will have a color palette of up to 4 different colors
// the palettes will work by storing the indices of the colors they want
// from the Renderer's colorPalette

// colors will most often be referenced by their so called "integer form"
// where there are 3 digits to represent the RGB values of a color
// they will look 502 for r5 g0 b2, anything above 999 means transparent
class ColorPalette
{
private:
	static constexpr uint8_t NUM_COLORS{ SpriteSheet::getPixelsPerByte() };
	static constexpr uint8_t DEFAULT_TRANSPARENT_INDEX{ 0 };	// if a sprite has transparency, its at this index

private:
	uint8_t colors[NUM_COLORS];	// indices of colors in renderer's color palette

private:
	const uint8_t parseIntColorToIndex(const uint16_t color) const;

public:
	ColorPalette();

	// takes in colors in integer form, meaning base Color::MAX_VALUE (5) notation
	// eg: if you wanted to represent R:5, G:2, B:3, you would simply do 523. For transparency, do -1 or >999
	ColorPalette(const uint16_t c1, const uint16_t c2, const uint16_t c3, const uint16_t c4);	// colors in integer form

	// creates a color pallet based on a single color
	ColorPalette(const Renderer& renderer, const uint16_t fillColorInt, const bool opaque, const uint8_t saturationRange = 0);

	const bool containsTransparency() const;

	void setColors(const uint16_t c1, const uint16_t c2, const uint16_t c3, const uint16_t c4);
	void setColor(const uint8_t ci, const uint16_t color);

	const uint8_t* getColors() const { return this->colors; }

	static inline constexpr uint8_t getNumColors() { return NUM_COLORS; }
};