#include "Color.h"

void Color::makeTransparent()
{
	this->data = Color::TRANSPARENT;
}

const bool Color::isTransparent() const
{
	return this->data == Color::TRANSPARENT;
}

void Color::setData(uint8_t r, uint8_t g, uint8_t b)
{
	r = Math::clamp(r, MIN_VAL, MAX_VAL);
	g = Math::clamp(g, MIN_VAL, MAX_VAL);
	b = Math::clamp(b, MIN_VAL, MAX_VAL);

	data = (r << RED_OFFSET) | (g << GREEN_OFFSET) | (b << BLUE_OFFSET);
}