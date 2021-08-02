#include "Vector.h"

#include <iostream>

void Vec2i::print() const
{
	std::cout << '(' << this->x << ", " << this->y << ")\n";
}