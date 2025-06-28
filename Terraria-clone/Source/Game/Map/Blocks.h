#pragma once
#include <vector>
#include "Block.h"

inline std::vector<Block> Blocks = {
	Block(TextureName::AIR),
	Block(TextureName::DIRT_TEXTURE_1),
	Block(TextureName::DIRT_TEXTURE_2),
	Block(TextureName::GRASS_TEXTURE_1),
	Block(TextureName::STONE_TEXTURE_1)
};

enum BLOCKS
{
	AIR = 0,
	DIRT1 = 1,
	DIRT2 = 2,
	GRASS1 = 3,
	STONE1 = 4,
};