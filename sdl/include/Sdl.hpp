//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml interface
//

#ifndef SDL_HPP_
#define SDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "IGraphical.hpp"

namespace arcade {
class Sdl : public IGraphical {
      public:
	Sdl();
	std::string getGame() const;
	std::string getNickName() const;
	std::string getLib() const;
	int getKey();
	int displayMap(std::vector<std::vector<uint16_t>> map,
		       entities_t entities);
	int menu(const std::vector<std::string> &games,
		 const std::vector<std::string> &lib);
	int changeMenu(SDL_Keycode key, bool whichLib);
	bool isOpen() const;
	~Sdl();
	void loadText(std::vector<std::tuple<SDL_Texture *, SDL_Rect>> &tGames,
		      const std::vector<std::string> &games);
	void displayGames(std::vector<SDL_Texture *> &tGames, size_t index);
	void printMenu(std::vector<std::tuple<SDL_Texture *, SDL_Rect>> _tLibs,
		       int x, size_t index);
	int printNick();
	int printScore();
	int printBack();

      private:
	bool _isOpen;
	TTF_Font *_commodor;
	SDL_Window *_window;
	size_t _indexGame;
	size_t _indexLib;
	std::string _nickName;
	std::string _game;
	std::string _lib;
	SDL_Renderer *_renderer;
	SDL_Texture *_texture;

	SDL_Texture *_menuTexture;
	SDL_Rect _menuPos;
};
extern "C" IGraphical *create_object();
} // namespace arcade

#endif /* !SDL_HPP_ */
