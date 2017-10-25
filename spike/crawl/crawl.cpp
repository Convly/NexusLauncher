#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

int main()
{
	std::string path = "./";
	for (auto & p : fs::directory_iterator(path)) {
		std::cout << p << std::endl;
	}
	return 0;
}