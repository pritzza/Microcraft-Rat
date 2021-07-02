#pragma once

#include <cstdint>

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
	const uint8_t* getColors() const { return this->colors; }
};