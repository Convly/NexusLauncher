#include <iostream>
#include "Launcher.hpp"

int main(int ac, char **av)
{

	nx::Launcher launcher(ac, av);
	return launcher.run();
}
