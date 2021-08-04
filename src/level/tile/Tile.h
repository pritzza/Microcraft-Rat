#pragma once

#include "TileBases.h"
#include "TileFeatures.h"
#include "TileFlavor.h"

#include "../../util/Direction.h"

// what is actually stored in each chunk to make up the world
class Tile
{
public:
	TileBases::ID baseID{ TileBases::ID::Grass };
	TileFeatures::ID featureID{ TileFeatures::ID::None };

	// say a flower only takes the top right tile component
	// meanwhile a tree would take up all the components
	bool featurePlacement[TileData::NUM_COMPONENTS]{ false };

	// storing dir doesnt work because there are 4 dirs that need to be stored
	DetailedDirection directions[TileData::NUM_COMPONENTS]{ DetailedDirection::Center };
	TileFlavor::Value flavors[TileData::NUM_COMPONENTS]{ TileFlavor::Value::None };

};