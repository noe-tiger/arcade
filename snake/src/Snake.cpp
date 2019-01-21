//
// EPITECH PROJECT, 2018
// acarde
// File description:
// snake game
//

#include <sstream>
#include <random>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <SFML/Graphics.hpp>

#include "Snake.hpp"

namespace arcade {
Snake::Snake()
	: _key(KEY_LEFT)
	, _start(std::chrono::high_resolution_clock::now())
	, _entities()
	, _head({17, 9})
	, _score(0)
{
	_snake.push_back(_head);
	_snake.push_back({17, 10});
	_snake.push_back({17, 11});
	loadMap();
}

void Snake::loadMap()
{
	std::string line;
	std::string token;
	auto size = 0;

	std::stringstream ss(MAP);
	std::string item;
	while (std::getline(ss, item, '\n')) {
		_map.resize(_map.size() + 1);
		for (size_t i = 0; i < item.length(); ++i)
			_map[size].push_back(item[i]);
		++size;
	}
}

IGame::status_e Snake::getStatus() const
{
	return _status;
}

void Snake::sendKey(int key)
{
	if (key >= KEY_DOWN && key <= KEY_RIGHT) {
		if (key == KEY_LEFT or key == KEY_RIGHT) {
			if (key == KEY_LEFT and _key == KEY_RIGHT)
				return;
			if (key == KEY_RIGHT and _key == KEY_LEFT)
				return;
		}
		if (key == KEY_DOWN or key == KEY_UP) {
			if (key == KEY_DOWN and _key == KEY_UP)
				return;
			if (key == KEY_UP and _key == KEY_DOWN)
				return;
		}
		_key = key;
	}
}

const std::vector<std::vector<uint16_t>> &Snake::getMap() const
{
	return _map;
}

const entities_t &Snake::getEntities() const
{
	return _entities;
}

int Snake::getScore() const
{
	return _score;
}

void Snake::move_key()
{
	switch (_key) {
	case KEY_DOWN: {
		_head.first += 1;
		break;
	}
	case KEY_UP: {
		_head.first -= 1;
		break;
	}
	case KEY_LEFT: {
		_head.second -= 1;
		break;
	}
	case KEY_RIGHT: {
		_head.second += 1;
		break;
	}
	}
}

void Snake::getFreeSpace()
{
	auto x = 0;
	auto y = 0;
	for (const auto &line : _map) {
		x = 0;
		for (const auto &char_c : line) {
			if (char_c == ' ')
				_freeSpace.push_back({y, x});
			x += 1;
		}
		y += 1;
	}
}

int Snake::countApple()
{
	int x;
	int y = 0;
	int nb = 0;

	for (const auto &line : _map) {
		x = 0;
		for (const auto &char_c : line) {
			if (char_c == '@')
				nb += 1;
			x += 1;
		}
		y += 1;
	}
	return nb;
}
void Snake::setApple()
{
	auto nb = 0 + rand() % ((_freeSpace.size() + 1) - 0);
	if (countApple() == 0 or countApple() < 2) {
		_map[_freeSpace[nb].first][_freeSpace[nb].second] = APPLE;
		_freeSpace.clear();
	}
}

void Snake::removeSnake()
{
	for (const auto &parts : _snake) {
		_map[parts.first][parts.second] = EMPTY;
	}
	_map[_snake.back().first][_snake.back().second] = EMPTY;
}

void Snake::moveSnake()
{
	for (auto i = _snake.size() - 1; i > 0; --i) {
		_snake[i].first = _snake[i - 1].first;
		_snake[i].second = _snake[i - 1].second;
	}
	_snake[0].first = _head.first;
	_snake[0].second = _head.second;
}

void Snake::putSnake()
{
	for (const auto &parts : _snake) {
		_map[parts.first][parts.second] = SNAKE_BODY;
	}
	_map[_head.first][_head.second] = SNAKE_HEAD;
	_map[_snake.back().first][_snake.back().second] = SNAKE_TAIL;
}

void Snake::play()
{
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _start)
		    .count()
	    >= 500) {
		_start = std::chrono::high_resolution_clock::now();
		move_key();
		if (_map[_head.first][_head.second] == WALL
		    or _map[_head.first][_head.second] == SNAKE_BODY
		    or _map[_head.first][_head.second] == SNAKE_TAIL)
			_status = LOSE;
		if (_map[_head.first][_head.second] == APPLE) {
			_snake.push_back(
				{_snake.back().first, _snake.back().second});
			_score += 10;
		}
		removeSnake();
		moveSnake();
		putSnake();
		getFreeSpace();
		setApple();
	}
}

extern "C" IGame *create_game()
{
	return new Snake;
}
} // namespace arcade
