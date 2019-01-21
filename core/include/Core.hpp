//
// EPITECH PROJECT, 2018
// arcade
// File description:
// core game
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dirent.h>

#include <string>

#include "IGraphical.hpp"
#include "IGames.hpp"

namespace arcade {
class Core {
      public:
	Core(const std::string &libPath);
	void loadGame(const std::string &gamePath);
	void loadLib(const std::string &libPath);
	void menu();
	void play();
	void quit();
	bool isOpen() const;

      private:
	void saveScore();
	void *_graphHandle = NULL;
	void *_gameHandle = NULL;
	bool _isOpen = false;
	std::vector<std::string> _games;
	std::vector<std::string> _libs;
	IGraphical *_currentLib = NULL;
	IGame *_currentGame = NULL;
};
bool loadDir(std::vector<std::string> &container,
	     const std::string &folderName);
} // namespace arcade

#endif /* !CORE_HPP_ */
