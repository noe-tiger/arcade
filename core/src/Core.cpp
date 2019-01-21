//
// EPITECH PROJECT, 2018
// acarde
// File description:
// core game
//

#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <ncurses.h>

#include <iostream>
#include <exception>
#include <fstream>
#include <algorithm>
#include <ios>

#include "Exceptions.hpp"
#include "Core.hpp"

namespace arcade {
static void sigHandler(int sig)
{
	if (sig == SIGINT) {
		std::cerr << "Received a SIGINT" << std::endl;
		exit(0);
	}
}

Core::Core(const std::string &libPath)
{
	try {
		loadLib(libPath);
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		exit(84);
	}
	signal(SIGINT, sigHandler);
}

void Core::loadLib(const std::string &libPath)
{
	if (_graphHandle) {
		dlclose(_graphHandle);
		_graphHandle = nullptr;
	}
	_graphHandle = dlopen(libPath.c_str(), RTLD_LAZY);
	std::cerr << "Loading lib : " + libPath << std::endl;
	if (!_graphHandle) {
		std::cerr << std::string(dlerror()) << std::endl;
		exit(84);
	}
	dlerror();
	IGraphical *(*create)() =
		(IGraphical * (*)()) dlsym(_graphHandle, "create_object");
	if (!create) {
		std::cerr << std::string(dlerror()) << std::endl;
		exit(84);
	}
	_currentLib = (IGraphical *)create();
	_isOpen = true;
}

void Core::loadGame(const std::string &gamePath)
{
	if (_gameHandle) {
		dlclose(_gameHandle);
		_graphHandle = nullptr;
	}
	_gameHandle = dlopen(gamePath.c_str(), RTLD_LAZY);
	std::cerr << "Loading game : " + gamePath << std::endl;
	if (!_gameHandle) {
		std::cerr << std::string(dlerror()) << std::endl;
		exit(84);
	}
	dlerror();
	IGame *(*create)() = (IGame * (*)()) dlsym(_gameHandle, "create_game");
	if (!create) {
		std::cerr << std::string(dlerror()) << std::endl;
		exit(84);
	}
	_currentGame = (IGame *)create();
}

bool Core::isOpen() const
{
	return _isOpen;
}

void Core::menu()
{
	_games.clear();
	_libs.clear();
	loadDir(_games, "games/");
	loadDir(_libs, "lib/");
	_currentLib->menu(_games, _libs);
	if (!_currentLib->getGame().empty())
		loadGame(_currentLib->getGame());
}

void Core::quit()
{
	if (_gameHandle) {
		dlclose(_gameHandle);
		_gameHandle = NULL;
	}
	if (_graphHandle) {
		dlclose(_graphHandle);
		_graphHandle = NULL;
	}
	_isOpen = false;
}

void Core::play()
{
	size_t lib = 0;
	size_t game = 0;

	if (_currentGame == NULL) {
		std::cerr << "Error : No proper game selected" << std::endl;
		_isOpen = false;
		return;
	}
	while (_currentGame->getStatus() == IGame::PLAYING
	       and _currentLib->isOpen()) {
		_currentLib->displayMap(_currentGame->getMap(),
					_currentGame->getEntities());
		int key = _currentLib->getKey();
		if (key == KEY_PPAGE) {
			delete _currentLib;
			lib = (lib + 1 >= _libs.size()) ? 0 : lib + 1;
			loadLib(_libs[lib]);
		}
		else if (key == KEY_NPAGE) {
			delete _currentLib;
			lib = (lib > 0) ? lib - 1 : _libs.size() - 1;
			loadLib(_libs[lib]);
		}
		else if (key == KEY_HOME) {
			delete _currentGame;
			game = (game + 1 >= _games.size()) ? 0 : game + 1;
			loadGame(_games[game]);
		}
		else if (key == KEY_END) {
			delete _currentGame;
			game = (game > 0) ? game - 1 : _games.size() - 1;
			loadGame(_games[game]);
		}
		else if (key == 'r') {
			delete _currentGame;
			loadGame(_games[game]);
		}
		_currentGame->sendKey(key);
		_currentGame->play();
		if (!_currentLib->isOpen()) {
			_currentGame = NULL;
			exit(0);
		}
	}
	saveScore();
}

void Core::saveScore()
{
	std::ofstream fileScore;

	fileScore.open("score.dat", std::ios::app);
	if (!fileScore.is_open())
		std::cerr << "Error : unable to save current score"
			  << std::endl;
	else {
		std::string gameName;
		std::string nickname = _currentLib->getNickName();
		if (nickname.empty())
			nickname = "Anonymous";
		size_t pos = _currentLib->getGame().find("lib_arcade_");
		if (pos != std::string::npos) {
			gameName = _currentLib->getGame().substr(pos + 11);
			size_t n = gameName.find(".so");
			if (n != std::string::npos)
				gameName.erase(n, 3);
		}
		fileScore << "\"" << nickname << "\" " << gameName
							<< " " << _currentGame->getScore() << std::endl;
	}
}

static bool endsWith(const std::string &mainStr)
{
	return mainStr.size() >= 3
	       and mainStr.compare(mainStr.size() - 3, 3, ".so");
}

bool loadDir(std::vector<std::string> &container, const std::string &folderName)
{
	DIR *directory;
	struct dirent *dirent;

	directory = opendir(folderName.c_str());
	if (!directory)
		return false;
	while ((dirent = readdir(directory)))
		if (dirent->d_type == DT_REG)
			container.push_back(
				std::string(folderName + dirent->d_name));
	closedir(directory);
	sort(container.begin(), container.end());
	container.erase(
		std::remove_if(container.begin(), container.end(), endsWith),
		container.end());
	return true;
}
} // namespace arcade
