//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml interface
//

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "IGraphical.hpp"
#include "Sprite.hpp"

namespace arcade {
class Sfml : public IGraphical {
      public:
	Sfml();
	std::string getGame() const;
	std::string getNickName() const;
	std::string getLib() const;
	int getKey();
	int displayMap(std::vector<std::vector<uint16_t>> map,
		       entities_t entities);
	int menu(const std::vector<std::string> &games,
		 const std::vector<std::string> &lib);
	bool isOpen() const;
	~Sfml();

      protected:
	void displaySnake(std::vector<std::vector<uint16_t>> &map, size_t i,
			  size_t j);
	void drawEntities(entities_t entities);
	void cathodeEffect();
	void refreshWin();
	void displayName();
	int keyHandler();
	void displayGames(std::vector<sf::Text> &tGames, size_t index);	
	void displayLibs(std::vector<sf::Text> &tLibs);
	void loadText(std::vector<sf::Text> &tGames,
		      const std::vector<std::string> &games);
	template <typename T> sf::Color *getPixel(T x, T y);
	void putPixel(size_t x, size_t y, sf::Color color);
	void putRect(size_t x, size_t y, size_t size, sf::Color color);
	void putEmptyRect(sf::Vector2u pos, sf::Vector2u size, size_t offset,
			  sf::Color color);
	void putRect(size_t x, size_t y, sf::Vector2u size, sf::Color color);
	std::string _lastScore;
	bool _isOpen = true;
	int _key;
	sf::RenderWindow _window;
	std::vector<Sprite> _sprites;
	sf::Font _font;
	sf::Uint8 *_pixels;
	std::string _nickname;
	size_t _size;
	std::string _game;
	std::string _lib;
};
extern "C" IGraphical *create_object();
} // namespace arcade

#endif /* !SFML_HPP_ */
