#include "Tile.h"

#include "../../util/Random.h"

void Tile::update(const double time)
{
	const TileBaseData& base{ TileBases::getBase(baseID) };
	const TileFeatureData& feature{ TileFeatures::getFeature(featureID) };

	// we're assigning this hundreds of times each frame which prolly aint the best idea
	// ideally only do this once per tileBaseID
	if(base.animationTickRate != 0)
		flavorBaseAnimationOffset.setValue(time / base.animationTickRate);

	if (feature.animationTickRate != 0)
		flavorFeatureAnimationOffset.setValue(time / feature.animationTickRate);
}