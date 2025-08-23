#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <pathUtils.hpp>

namespace fs = std::filesystem;

extern 	std::unordered_map<std::string, SDL_Texture*> g_Textures;

class AssetManager {

public:

	void LoadTextures(std::filesystem::path AssetsDir, SDL_Renderer* renderer);
	
};




