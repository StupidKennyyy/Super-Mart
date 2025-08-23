#pragma once

enum TileType {
	Air,
	Ground
};

struct tile {
	TileType Type{ TileType::Air };
	Transform Tf;
};

