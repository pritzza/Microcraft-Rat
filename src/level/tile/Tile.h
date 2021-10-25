#pragma once

#include "TileBase.h"
#include "TileFeature.h"

// what is actually stored in each chunk to make up the world
class Tile
{
private:
	TileBase base{ TileBase::ID::Grass };
	TileFeature feature{ TileFeature::ID::None };

public:
	void update(const double time);

	const bool hasFeature() const { return !feature.isEmpty(); }

	void setBase(const TileBase::ID id);
	void setFeature(const TileFeature::ID id);

	const TileBase& getBase() const			{ return base;		}
	const TileFeature& getFeature() const	{ return feature;	}

	TileBase& getBase()						{ return base;		}
	TileFeature& getFeature()				{ return feature;	}
};