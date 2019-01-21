//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml interface
//

#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#include "Sdl.hpp"

const std::string getScore()
{
        std::string line = "";
        std::string lastLine = "";
        std::ifstream fin;
        fin.open("score.dat");
        if (fin.is_open()) {
                while (getline(fin, line))
                {
                        if (line.size() > 0)
                                lastLine = line;
                }
                fin.close();
        }
        return lastLine;
}

namespace arcade {
Sdl::Sdl()
	: _indexGame(0)
	, _indexLib(0)
{
	SDL_Surface *img;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) == -1)
		exit(84);
	SDL_CreateWindowAndRenderer(600, 600, 0, &_window, &_renderer);
	if (TTF_Init() == -1)
		return; // throw error
	_commodor = TTF_OpenFont("fonts/commodore-64.ttf", 19);
	_isOpen = true;
	img = IMG_Load("sprites/sfml_menu_background.png");
	_menuTexture = SDL_CreateTextureFromSurface(_renderer, img);
	SDL_FreeSurface(img);
	_menuPos = {0, 0, 1600, 600};
}

Sdl::~Sdl()
{
	SDL_DestroyTexture(_menuTexture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	SDL_Quit();
}

int Sdl::getKey()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			_isOpen = false;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_RETURN)
				return '\n';
			else if (event.key.keysym.sym == SDLK_LEFT)
				return KEY_LEFT;
			else if (event.key.keysym.sym == SDLK_ESCAPE)
				_isOpen = false;
			else if (event.key.keysym.sym == SDLK_RIGHT)
				return KEY_RIGHT;
			else if (event.key.keysym.sym == SDLK_UP)
				return KEY_UP;
			else if (event.key.keysym.sym == SDLK_DOWN)
				return KEY_DOWN;
			else if (event.key.keysym.sym == SDLK_PAGEDOWN)
				return KEY_NPAGE;
			else if (event.key.keysym.sym == SDLK_PAGEUP)
				return KEY_PPAGE;
			else if (event.key.keysym.sym == SDLK_HOME)
				return KEY_HOME;
			else if (event.key.keysym.sym == SDLK_END)
				return KEY_END;
			else if (event.key.keysym.sym == SDLK_r)
				return 'r';
			else
				return event.key.keysym.sym;
		}
	}
	return 0;
}

int Sdl::changeMenu(SDL_Keycode key, bool whichLib)
{
	if (whichLib) {
		if (key == SDLK_DOWN)
			_indexLib++;
		if (key == SDLK_UP)
			_indexLib == 0 ? _indexLib = SIZE_MAX : _indexLib--;
	}
	else {
		if (key == SDLK_DOWN)
			_indexGame++;
		if (key == SDLK_UP)
			_indexGame == 0 ? _indexGame = SIZE_MAX : _indexGame--;
	}
	return 0;
}

void Sdl::loadText(std::vector<std::tuple<SDL_Texture *, SDL_Rect>> &tGames,
		   const std::vector<std::string> &games)
{
	for (size_t i = 0; i < games.size(); ++i) {
		size_t pos = games[i].find("lib_arcade_");
		std::string dispStr;
		if (pos != std::string::npos) {
			dispStr = games[i].substr(pos + 11);
			size_t n = dispStr.find(".so");
			if (n != std::string::npos)
				dispStr.erase(n, 3);
		}
		else
			dispStr = games[i];
		SDL_Color White = {255, 255, 255, 0};
		SDL_Surface *surfaceMessage =
			TTF_RenderText_Solid(_commodor, dispStr.c_str(), White);
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 10;
		rect.w = surfaceMessage->w;
		rect.h = surfaceMessage->h;
		tGames.push_back(std::tuple<SDL_Texture *, SDL_Rect>(
			SDL_CreateTextureFromSurface(_renderer, surfaceMessage),
			rect));
		SDL_FreeSurface(surfaceMessage);
	}
}

void Sdl::printMenu(std::vector<std::tuple<SDL_Texture *, SDL_Rect>> _tLibs,
		    int x, size_t index)
{
	for (size_t i = 0; i < _tLibs.size(); i++) {
		if (i > 0) {
			std::get<1>(_tLibs[i]).y =
				std::get<1>(_tLibs[i - 1]).y
				+ std::get<1>(_tLibs[i - 1]).h;
		}
		if (i == index)
			SDL_SetTextureColorMod(std::get<0>(_tLibs[i]), 255, 0,
					       0);
		else
			SDL_SetTextureColorMod(std::get<0>(_tLibs[i]), 255, 255,
					       255);
		std::get<1>(_tLibs[i]).x = x;
		SDL_RenderCopy(_renderer, std::get<0>(_tLibs[i]), NULL,
			       &std::get<1>(_tLibs[i]));
	}
}

int Sdl::printNick()
{
	std::string str = "Nickname : ";
	str += _nickName;
	SDL_Color White = {255, 255, 255, 0};
	SDL_Surface *surfaceMessage =
		TTF_RenderText_Solid(_commodor, str.c_str(), White);
	SDL_Rect rect;
	rect.x = 10;
	rect.y = 550;
	rect.w = surfaceMessage->w;
	rect.h = surfaceMessage->h;
	SDL_RenderCopy(_renderer,
		       SDL_CreateTextureFromSurface(_renderer, surfaceMessage),
		       NULL, &rect);
	SDL_FreeSurface(surfaceMessage);
	return 0;
}

int Sdl::printScore()
{
	std::string str = "Score : " + getScore();
	SDL_Color White = {255, 255, 255, 0};
	SDL_Surface *surfaceMessage =
		TTF_RenderText_Solid(_commodor, str.c_str(), White);
	SDL_Rect rect;
	rect.x = 10;
	rect.y = 500;
	rect.w = surfaceMessage->w;
	rect.h = surfaceMessage->h;
	SDL_RenderCopy(_renderer,
		       SDL_CreateTextureFromSurface(_renderer, surfaceMessage),
		       NULL, &rect);
	SDL_FreeSurface(surfaceMessage);
	return 0;
}

int Sdl::printBack()
{
	static int i = 0;

	if (!_menuTexture)
		return (-1);
	if (i++ > 10) {
		_menuPos.x--;
		i = 0;
	}
	SDL_RenderCopy(_renderer, _menuTexture, NULL, &_menuPos);
	_menuPos.x += 1600;
	SDL_RenderCopy(_renderer, _menuTexture, NULL, &_menuPos);
	_menuPos.x -= 1600;
	if (_menuPos.x == -1600)
		_menuPos.x = 0;
	return 0;
}

int Sdl::menu(const std::vector<std::string> &games,
	      const std::vector<std::string> &libs)
{
	bool whichLib = false;
	std::vector<std::tuple<SDL_Texture *, SDL_Rect>> _tGames;
	std::vector<std::tuple<SDL_Texture *, SDL_Rect>> _tLibs;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;

	_isOpen = true;
	loadText(_tGames, games);
	loadText(_tLibs, libs);
	while (!quit) {
		_game = games[_indexGame];
		_lib = libs[_indexLib];
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = SDL_TRUE;
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = SDL_TRUE;
				if (event.key.keysym.sym == SDLK_RETURN)
					return (0);
				if (event.key.keysym.sym == SDLK_LEFT)
					whichLib = !whichLib;
				if (event.key.keysym.sym == SDLK_RIGHT)
					whichLib = !whichLib;
				changeMenu(event.key.keysym.sym, whichLib);
				if (_indexLib > libs.size())
					_indexLib = libs.size() - 1;
				if (_indexGame > games.size())
					_indexGame = games.size() - 1;
				if (_indexGame > games.size() - 1)
					_indexGame = 0;
				if (_indexLib > libs.size() - 1)
					_indexLib = 0;
				if (event.key.keysym.sym > 31
				    && event.key.keysym.sym < 127)
					_nickName.push_back(
						event.key.keysym.sym);
				if (event.key.keysym.sym == 8
				    && _nickName.size() > 0)
					_nickName.pop_back();
			}
		}
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
		SDL_RenderClear(_renderer);
		printBack();
		printMenu(_tGames, 10, _indexGame);
		printMenu(_tLibs, 400, _indexLib);
		printNick();
		printScore();
		SDL_RenderPresent(_renderer);
	}
	_isOpen = false;
	exit(0);
	return 0;
}

int Sdl::displayMap(std::vector<std::vector<uint16_t>> map, entities_t entities)
{
	size_t siz = 600
		     / static_cast<int>((map.size() > map[0].size()
						 ? map.size()
						 : map[0].size()));
	SDL_Event event;
	SDL_Rect pos;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			_isOpen = false;
		if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				_isOpen = false;
	}
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	for (size_t i = 0; i < map.size(); i++)
		for (size_t j = 0; j < map[i].size(); j++) {
			pos = {static_cast<int>(siz * j),
			       static_cast<int>(siz * i), static_cast<int>(siz),
			       static_cast<int>(siz)};
			if (map[i][j] == WALL)
				SDL_SetRenderDrawColor(_renderer, 120, 0, 0, 0);
			else if (map[i][j] == SNAKE_HEAD
				 || map[i][j] == SNAKE_BODY
				 || map[i][j] == SNAKE_TAIL)
				SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 0);
			else if (map[i][j] == APPLE)
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 0);
			else if (map[i][j] == FOOD)
				SDL_SetRenderDrawColor(_renderer, 120, 120, 0,
						       0);
			else
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(_renderer, &pos);
		}
	for (size_t i = 0; i < entities.size(); ++i) {
		pos = {static_cast<int>(siz * entities[i].second.first),
		       static_cast<int>(siz * entities[i].second.second),
		       static_cast<int>(siz), static_cast<int>(siz)};
		if (entities[i].first == 'P')
			SDL_SetRenderDrawColor(_renderer, 150, 10, 10, 120);
		else if (entities[i].first == 'G')
			SDL_SetRenderDrawColor(_renderer, 200, 25, 25, 120);
		else if (entities[i].first == 'B')
			SDL_SetRenderDrawColor(_renderer, 25, 25, 200, 120);
		SDL_RenderFillRect(_renderer, &pos);
	}
	SDL_RenderPresent(_renderer);
	return 0;
}

bool Sdl::isOpen() const
{
	return _isOpen;
}
std::string Sdl::getGame() const
{
	return _game;
}
std::string Sdl::getNickName() const
{
	return _nickName;
}
std::string Sdl::getLib() const
{
	return _lib;
}
extern "C" IGraphical *create_object()
{
	return new Sdl;
}
} // namespace arcade
