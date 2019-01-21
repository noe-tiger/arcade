//
// EPITECH PROJECT, 2018
// arcade
// File description:
// main program frame
//

#include <dlfcn.h>

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "IGames.hpp"
#include "IGraphical.hpp"
#include "Core.hpp"

static void usage()
{
	std::cerr << "Usage :" << std::endl
		  << "\t./arcade [graphiclib.so]" << std::endl;
}

int main(int ac, char *av[ac])
{
	if (ac != 2) {
		usage();
		return 84;
	}
	arcade::Core core((std::string(av[1])));
	while (core.isOpen()) {
		core.menu();
		std::srand(std::time(nullptr));
		core.play();
	}
	core.quit();
	return 0;
}
