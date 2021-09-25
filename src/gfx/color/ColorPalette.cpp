#include "ColorPalette.h"

#include "Color.h"
#include "../Renderer.h"

#include "../../util/Math.h"

#include <cmath>

#include <iostream>

ColorPalette::ColorPalette(const uint16_t ci1, const uint16_t ci2, const uint16_t ci3, const uint16_t ci4)
{
	this->setColors(ci1, ci2, ci3, ci4);
}

ColorPalette::ColorPalette(const Renderer& renderer, const uint16_t fillColorInt, const bool transparent, const uint8_t saturationRange)
{
	// get the color stored in the renderer's palette at the index equal to fillColorInt
	const Color& c{ renderer.getPaletteColor( parseIntColorToIndex(fillColorInt) ) };
	const uint8_t r{ c.getRed()   };
	const uint8_t g{ c.getGreen() };
	const uint8_t b{ c.getBlue()  };

	if (transparent)
		colors[DEFAULT_TRANSPARENT_INDEX] = Renderer::getTransparentColor();

	for (int i = transparent; i < NUM_COLORS; ++i)
	{
		const float saturationMultiplier{ (i - transparent / (NUM_COLORS - transparent) * 1.f) };

		colors[i] = renderer.getPaletteIndex( Color{
			static_cast<uint8_t>( Math::round(r * saturationMultiplier) ),
			static_cast<uint8_t>( Math::round(g * saturationMultiplier) ),
			static_cast<uint8_t>( Math::round(b * saturationMultiplier) )
			});
	}
}

const bool ColorPalette::containsTransparency() const
{
	for (int i = 0; i < NUM_COLORS; ++i)
		if (colors[i] == Renderer::getTransparentColor())
			return true;

	return false;
}

void ColorPalette::setColors(const uint16_t ci1, const uint16_t ci2, const uint16_t ci3, const uint16_t ci4)
{
	colors[0] = parseIntColorToIndex(ci1);
	colors[1] = parseIntColorToIndex(ci2);
	colors[2] = parseIntColorToIndex(ci3);
	colors[3] = parseIntColorToIndex(ci4);
}

void ColorPalette::setColor(const uint8_t ci, const uint16_t color)
{
	colors[ci] = parseIntColorToIndex(color);
}


// idea on how to make colors
//2<<RED | 3<<GREEN | 5<<BLUE

const uint8_t ColorPalette::parseIntColorToIndex(const uint16_t color) const
{
	// if color is above 999 or -1 (unsigned underflow), it means its transparent
	static constexpr uint16_t TRANSPARENT_THRESHOLD = -1;

	const bool	  a = color == TRANSPARENT_THRESHOLD;

	const uint8_t r = Math::clamp( ((color % 1000) / 100), Color::getMinValue(), Color::getMaxValue());
	const uint8_t g = Math::clamp( ((color % 100 ) / 10 ), Color::getMinValue(), Color::getMaxValue());
	const uint8_t b = Math::clamp( ((color % 10  ) / 1  ), Color::getMinValue(), Color::getMaxValue());

	if (a)
		return Renderer::getTransparentColor();
	
	static constexpr uint8_t CR{ Color::getColorRange() };

	// when we generate the color palette, its a triple for loop going r g b
	// this is kinda how we reverse engineer the indices of the color palette
	return (r * CR * CR) + (g * CR) + b;
}