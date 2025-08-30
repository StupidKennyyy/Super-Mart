
#include <asset_manager.hpp>


std::unordered_map<std::string, SDL_Texture*> g_Textures;


void AssetManager::LoadTextures(std::filesystem::path AssetsDir, SDL_Renderer* renderer)
{
	std::cout << "Assets Path -> " << AssetsDir.string() << std::endl;

	if (!fs::exists(AssetsDir) && !fs::is_directory(AssetsDir))
		return;

	for (const auto& entry : fs::directory_iterator(AssetsDir))
	{

		//std::cout << entry.path() << std::endl;

		fs::path filePath = entry.path();

		std::string pathStr = filePath.string();

		std::string fileName = filePath.filename().string();

		SDL_Texture* texture = IMG_LoadTexture(renderer, pathStr.c_str());

		if (!texture)
		{
			std::cerr << "Failed to load image at " << pathStr << ". "<< SDL_GetError() << std::endl;
			continue;

		}

		g_Textures[fileName] = texture;

		std::cout << "Loaded: " << fileName << std::endl;
		
	}

}

void AssetManager::DeloadTextures()
{
	for (auto pair : g_Textures)
	{
		SDL_DestroyTexture(pair.second);
	}

	g_Textures.clear();
}
