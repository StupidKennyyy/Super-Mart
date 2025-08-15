#pragma once

enum TileType {
	Air,
	Ground
};

struct Tile {
	TileType Type{ TileType::Air };
	Transform Tf;
};

