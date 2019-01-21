//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml interface
//

#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Sfml.hpp"

namespace arcade {
static const std::string getScore()
{
	std::string line;
	std::string lastLine;
	std::ifstream file;

	file.open("score.dat");
	if (file.is_open()) {
		while (getline(file, line))
			if (line.size() > 0)
				lastLine = line;
		file.close();
	}
	return lastLine;
}

Sfml::Sfml()
	: _window(sf::VideoMode(800, 600), "Arcade", 0)
{
	std::srand(std::time(nullptr));
	_pixels = new sf::Uint8[_window.getSize().x * _window.getSize().y * 4];
	_font.loadFromFile("fonts/commodore-64.ttf");
	loadSprites(_sprites, "sprites/");
	_lastScore = getScore();
}

Sfml::~Sfml()
{
	delete[] _pixels;
}

int Sfml::getKey()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::TextEntered)
			return (int)event.text.unicode;
		if (event.type == sf::Event::KeyPressed)
			switch (event.key.code) {
			case sf::Keyboard::Up:
				return KEY_UP;
			case sf::Keyboard::Down:
				return KEY_DOWN;
			case sf::Keyboard::Left:
				return KEY_LEFT;
			case sf::Keyboard::Right:
				return KEY_RIGHT;
			case sf::Keyboard::Escape:
				_isOpen = false;
			case sf::Keyboard::PageDown:
				return KEY_NPAGE;
			case sf::Keyboard::Home:
				return KEY_HOME;
			case sf::Keyboard::End:
				return KEY_END;
			case sf::Keyboard::R:
				return 'r';
			default:
				return -1;
			}
		if (event.type == sf::Event::Closed) {
			_isOpen = false;
			_window.close();
		}
	}
	return -1;
}

static void selection(size_t *index, size_t size, int key)
{
	if (key == sf::Keyboard::Up) {
		if (*index > 0)
			--(*index);
		else
			*index = size - 1;
	}
	if (key == sf::Keyboard::Down) {
		if (*index < size - 1)
			++(*index);
		else
			*index = 0;
	}
}

void Sfml::loadText(std::vector<sf::Text> &tGames,
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
		tGames.push_back(sf::Text(dispStr, _font, 20));
		tGames[i].setFillColor(sf::Color::Black);
		tGames[i].setPosition(_window.getSize().x / 10, 100 + i * 20);
	}
}

template <typename T> sf::Color *Sfml::getPixel(T x, T y)
{
	if (x < 0 or y < 0 or x > (T)_window.getSize().x
	    or y > (T)_window.getSize().y)
		return (nullptr);
	size_t pos = (y * _window.getSize().x + x) * 4;
	return (sf::Color *)&(_pixels[pos]);
}

void Sfml::cathodeEffect()
{
	static double h;

	_sprites[0].setPosition(0, h + std::rand() % 20);
	_window.draw(_sprites[0]);
	_sprites[0].setPosition(0, h - _window.getSize().y + std::rand() % 20);
	_window.draw(_sprites[0]);
	if (h > _window.getSize().y)
		h = std::rand() % 50;
	else
		h += std::rand() % 3;
}

void Sfml::displayGames(std::vector<sf::Text> &tGames, size_t index)
{
	for (size_t i = 0; i < tGames.size(); ++i) {
		if (index == i) {
			sf::Color color = sf::Color::Red;
			for (int a = 1; a < 5; ++a) {
				color.r = a * 50;
				color.g = a * i * 20;
				color.b = i * 70;
				putRect(_window.getSize().x / 10 + (a)-5,
					100 + (i * 20) + (a), (a * 3), color);
			}
			tGames[i].setFillColor(sf::Color(255, 255, 0, 160));
		}
		else {
			sf::Color clr;
			if (tGames[i].getString().find("/")
			    == std::string::npos)
				clr = sf::Color(0, 255, 0, 200);
			else
				clr = sf::Color(255, 0, 0, 200);
			tGames[i].setFillColor(clr);
		}
		_window.draw(tGames[i]);
	}
}

void Sfml::displayLibs(std::vector<sf::Text> &tLibs)
{
	for (size_t i = 0; i < tLibs.size(); ++i) {
		sf::Color color = sf::Color(255, 0, 0, 200);
		if (tLibs[i].getString().find("sfml") != sf::String::InvalidPos)
			color = sf::Color(0, 255, 0, 200);
		tLibs[i].setPosition(_window.getSize().x / 2, 100 + i * 20);
		tLibs[i].setFillColor(color);
		_window.draw(tLibs[i]);
	}
}

int Sfml::keyHandler()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b' and !_nickname.empty())
				_nickname.erase(_nickname.length() - 1, 1);
			else if (event.text.unicode >= ' '
				 and event.text.unicode < 127)
				_nickname.push_back(event.text.unicode);
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			return event.key.code;
		}
		if (event.type == sf::Event::Closed)
			_window.close();
	}
	return -1;
}

void Sfml::displayName()
{
	static sf::Color color(0, 0, 0);

	sf::Text name("Insert nickname : " + _nickname, _font, 20);
	name.setPosition(10, 10);
	name.setFillColor(sf::Color::Black);
	_window.draw(name);
	putEmptyRect(sf::Vector2u(10, 9),
		     sf::Vector2u(name.getString().getSize() * 16 + 10, 27), 3,
		     color);
	color.r += 1;
	color.g -= 2;
	color.b += 3;
}

int Sfml::menu(const std::vector<std::string> &games,
	       const std::vector<std::string> &libs)
{
	std::vector<sf::Text> tGames;
	std::vector<sf::Text> tLibs;
	sf::Text score(getScore(), _font, 20);
	size_t index = 0;
	double h = _window.getSize().x;

	_isOpen = true;
	loadText(tGames, games);
	loadText(tLibs, libs);
	score.setPosition(15, _window.getSize().y - 200);
	score.setFillColor(sf::Color(100, 0, 150, 200));
	while (_window.isOpen()) {
		_window.clear(sf::Color::Black);
		_sprites[1].setPosition(h, 0);
		_window.draw(_sprites[1]);
		_sprites[1].setPosition(h - _window.getSize().x * 2, 0);
		_window.draw(_sprites[1]);
		_key = keyHandler();
		selection(&index, tGames.size(), _key);
		if (_key == sf::Keyboard::Return) {
			_game = games[index];
			return 0;
		}
		displayGames(tGames, index);
		displayLibs(tLibs);
		displayName();
		_window.draw(score);
		refreshWin();
		h -= 0.7;
		if (h < 0)
			h = _window.getSize().x * 2;
	}
	return 0;
}

void Sfml::refreshWin()
{
	sf::Texture texture;
	sf::Sprite sprite;

	texture.create(_window.getSize().x, _window.getSize().y);
	texture.update(_pixels);
	sprite.setTexture(texture);
	_window.draw(sprite);
	for (size_t i = 0; i < _window.getSize().x * _window.getSize().y; ++i)
		((uint32_t *)_pixels)[i] = 0;
	cathodeEffect();
	_window.display();
}


void Sfml::putEmptyRect(sf::Vector2u pos, sf::Vector2u size, size_t offset,
			sf::Color color)
{
	putRect(pos.y, pos.x, sf::Vector2u(offset, size.x), color);
	putRect(pos.y + size.y - offset, pos.x, sf::Vector2u(offset, size.x),
		color);
	putRect(pos.y + offset, pos.x,
		sf::Vector2u(size.y - 2 * offset, offset), color);
	putRect(pos.y + offset, pos.x + size.x - offset,
		sf::Vector2u(size.y - 2 * offset, offset), color);
}

void Sfml::putRect(size_t x, size_t y, size_t size, sf::Color color)
{
	putRect(y, x, sf::Vector2u(size, size), color);
}

void Sfml::putPixel(size_t x, size_t y, sf::Color color)
{
	if (x < _window.getSize().x and y < _window.getSize().y) {
		size_t offset = (_window.getSize().x * y + x) * 4;
		_pixels[offset + 0] = color.r;
		_pixels[offset + 1] = color.g;
		_pixels[offset + 2] = color.b;
		_pixels[offset + 3] = color.a;
	}
}

void Sfml::putRect(size_t x, size_t y, sf::Vector2u size, sf::Color color)
{
	for (size_t i = 0; i < size.y; ++i)
		for (size_t j = 0; j < size.x; ++j)
			putPixel(i + y, j + x, color);
}

void Sfml::drawEntities(entities_t entities)
{
	for (size_t i = 0; i < entities.size(); ++i) {
		if (entities[i].first == 'P')
			putRect(_size * entities[i].second.first,
				_size * entities[i].second.second, _size,
				sf::Color(255, 255, 0, 200));
		else if (entities[i].first == 'G' or entities[i].first == 'g')
			putRect(_size * entities[i].second.first,
				_size * entities[i].second.second, _size,
				sf::Color(i * 10, i * 50, i * 100, 200));
	}
}

void Sfml::displaySnake(std::vector<std::vector<uint16_t>> &map, size_t i,
			size_t j)
{
	sf::Color color;

	if ((char)map[i][j] != EMPTY and (char) map[i][j] != WALL) {
		if ((char)map[i][j] == SNAKE_HEAD)
			color = {150, 100, 100, 200};
		else if ((char)map[i][j] == SNAKE_BODY)
			color = {200, 125, 125, 200};
		else if ((char)map[i][j] == SNAKE_TAIL)
			color = {255, 175, 175, 200};
		else if ((char)map[i][j] == APPLE)
			color = sf::Color(255, 0, 0, 200);
		if ((char)map[i][j] != '.')
			putRect(_size * j, _size * i, _size, color);
		else {
			color = sf::Color::Yellow;
			putRect(_size * j + 5, _size * i + 5, 5, color);
		}
	}
}

int Sfml::displayMap(std::vector<std::vector<uint16_t>> map,
		     entities_t entities)
{
	sf::Texture texture;
	sf::Sprite mapper;
	sf::Text info(
		"Press PageUp or PageDown\nto"
		"swap between libraries",
		_font, 10);

	_size = _window.getSize().y / map.size();
	_window.clear(sf::Color::Black);
	info.setPosition(_window.getSize().x - 210, 30);
	for (size_t i = 0; i < map.size(); ++i)
		for (size_t j = 0; j < map[i].size(); ++j) {
			if ((char)map[i][j] == WALL) {
				if (j + 1 < map[i].size()
				    and (char) map[i][j + 1] == WALL)
					putRect(i * _size + _size / 3.0,
						j * _size + _size / 3.0,
						sf::Vector2u(_size / 3.0,
							     _size * 4.0 / 3.0),
						sf::Color::White);
				if (i + 1 < map.size()
				    and (char) map[i + 1][j] == WALL)
					putRect(i * _size + _size / 3.0,
						j * _size + _size / 3.0,
						sf::Vector2u(_size * 4.0 / 3.0,
							     _size / 3.0),
						sf::Color::White);
			}
			displaySnake(map, i, j);
		}
	_window.draw(info);
	drawEntities(entities);
	refreshWin();
	return 0;
}

bool Sfml::isOpen() const
{
	return _isOpen;
}
std::string Sfml::getGame() const
{
	return _game;
}
std::string Sfml::getNickName() const
{
	return _nickname;
}
std::string Sfml::getLib() const
{
	return _lib;
}
extern "C" IGraphical *create_object()
{
	if (std::getenv("DISPLAY") == nullptr)
		exit(84);
	return new Sfml;
}
} // namespace arcade
