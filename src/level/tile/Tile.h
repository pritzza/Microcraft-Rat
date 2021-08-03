#pragma once

#include "TileBases.h"
#include "TileFeatures.h"

//#include "../../util/Direction.h"

class Tile
{
public:
	TileBases::ID baseID{TileBases::ID::Grass};
	TileFeatures::ID featureID{TileFeatures::ID::None};

	//DetailedDirection

};