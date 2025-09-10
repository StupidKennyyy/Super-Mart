
#include "pathUtils.hpp"

#include <Windows.h>
#include <iostream>

std::filesystem::path GetExecutablePath()
{
	
	std::cout << "Current working dir: " << std::filesystem::current_path() << "\n";

	char buffer[1024];

	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	return std::filesystem::path(buffer);

}

std::filesystem::path GetAssetsPath()
{

	auto exePath = GetExecutablePath();

	auto exeDir = exePath.parent_path();

	auto rootDir = exeDir.parent_path();

	return rootDir / "Assets";

}

