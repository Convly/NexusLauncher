#include <iostream>
#include "Launcher.hpp"

int main()
{

	nx::Launcher launcher;

	std::cout << launcher.getSystemByName("ui")->getName() << std::endl;
	return (0);
}
