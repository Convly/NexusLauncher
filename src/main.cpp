#include <iostream>
#include <filesystem>
#include "Launcher.hpp"

namespace fs = std::experimental::filesystem;

int main()
{
	std::string path = "./";
	for (auto & p : fs::directory_iterator(path)) {
		std::cout << "(" << fs::is_directory(p) << ")" << p << std::endl;
	}

	nx::Launcher launcher;

	std::cout << launcher.getSystemByName("ui")->getName() << std::endl;
	return (0);
}
