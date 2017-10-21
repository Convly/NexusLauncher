#include <iostream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
	std::string path = "./";
	for (auto & p : fs::directory_iterator(path)) {
		std::cout << "(" << fs::is_directory(p) << ")" << p << std::endl;
	}
	std::cout << "Hello World!" << std::endl;
	return (0);
}
