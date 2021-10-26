#pragma once

#include "TileBase.h"
#include "TileFeature.h"

// what is actually stored in each chunk to make up the world
// 
// so while tile is made up for many "structs", tile is a "class" and i want it to be the interface for
// all of the things underneath it, so from hence forth, you will do stuff like getBaseFlavorSprite() 
// rather than getBase().flavorSprite
class Tile
{
private:
	TileBase base{ TileBase::ID::Grass };
	TileFeature feature{ TileFeature::ID::None };

public:
	void update(const double time);

	const bool hasFeature() const			{ return !feature.isEmpty(); }

	void setBase(const TileBase::ID id);
	void setFeature(const TileFeature::ID id);

	const TileBase& getBase() const			{ return base;		}
	const TileFeature& getFeature() const	{ return feature;	}

	TileBase& getBase()						{ return base;		}
	TileFeature& getFeature()				{ return feature;	}
};