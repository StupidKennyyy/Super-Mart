
#include "pathUtils.hpp"

#include <Windows.h>

std::filesystem::path GetExecutablePath()
{

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

