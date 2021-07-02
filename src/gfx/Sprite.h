#pragma once

#include <cstdint>

struct Sprite
{
	// sprite sheet x/y start, width/height
	uint8_t x, y, w, h;

	//template<typename Coords, typename Dim>
	//Sprite(const Coords x, const Coords y, const Dim w, const Dim y)
	//	:
	//	x{ static_cast<uint8_t>( x ) },
	//	y{ static_cast<uint8_t>( y ) },
	//	w{ static_cast<uint8_t>( w ) },
	//	h{ static_cast<uint8_t>( h ) }
	//{}
};