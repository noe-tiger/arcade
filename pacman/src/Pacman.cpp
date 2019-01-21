//
// EPITECH PROJECT, 2018
// acarde
// File description:
// snake game
//


#include <unistd.h>
#include <sstream>
#include <random>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <queue>
#include <SFML/Graphics.hpp>

#include "Pacman.hpp"

namespace arcade {
Pacman::Pacman()
	: _key(KEY_LEFT)
	, _start(std::chrono::high_resolution_clock::now())
	, _miniStart(std::chrono::high_resolution_clock::now())
	, _miniStartIA(std::chrono::high_resolution_clock::now())
	, _startMoving(std::chrono::high_resolution_clock::now())
	, _reachPrev(false)
	, _direction(WEST)
	, _pacman(std::make_pair(17, 15))
	, _strong(false)
	, _ghost1(Ghost(13, 13, WEST))
	, _ghost2(Ghost(12, 13, EAST))
	, _ghost3(Ghost(11, 13, WEST))
	, _speed(500)
	, _score(0)
{
	_entities.push_back({'P', {17, 15}});
	_entities.push_back({'G', _ghost1.getPos()});
	_entities.push_back({'G', _ghost2.getPos()});
	_entities.push_back({'G', _ghost3.getPos()});
	loadMap();
}

void Pacman::loadMap()
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

const entities_t &Pacman::getEntities() const
{
	return _entities;
}


IGame::status_e Pacman::getStatus() const
{
	return _status;
}

void Pacman::sendKey(int key)
{
	if (key >= KEY_DOWN && key <= KEY_RIGHT)
		_key = key;
}

int Pacman::getScore() const
{
	return _score;
}


const std::vector<std::vector<uint16_t>> &Pacman::getMap() const
{
	return _map;
}

int Pacman::check_move()
{
	if (_direction == WEST and _pacman.first - 1 != -1
	    and _map[_pacman.second][_pacman.first - 1] == '#')
		return false;
	if (_direction == EAST
	    and _pacman.first < static_cast<int>(_map[0].size() - 1)
	    and _map[_pacman.second][_pacman.first + 1] == '#')
		return false;
	if (_direction == NORTH
	    and _map[_pacman.second - 1][_pacman.first] == '#')
		return false;
	if (_direction == SOUTH
	    and _map[_pacman.second + 1][_pacman.first] == '#')
		return false;
	return true;
}

void Pacman::move_key()
{
	direction_e prev = _direction;
	switch (_key) {
	case KEY_DOWN: {
		_direction = SOUTH;
		break;
	}
	case KEY_UP: {
		_direction = NORTH;
		break;
	}
	case KEY_LEFT: {
		_direction = WEST;
		break;
	}
	case KEY_RIGHT: {
		_direction = EAST;
		break;
	}
	}
	if (_direction != prev and (prev == EAST or prev == SOUTH)) {
		_pacman.second = ceil(_entities[0].second.second);
		_pacman.first = ceil(_entities[0].second.first);
	}
	else if (_direction != prev and (prev == NORTH or prev == WEST)) {
		_pacman.second = floor(_entities[0].second.second);
		_pacman.first = floor(_entities[0].second.first);
	}
	if (!check_move()) {
		return;
	}
	if (_map[_pacman.second][_pacman.first] == '.')
		_map[_pacman.second][_pacman.first] = ' ';
	if ((_direction == NORTH && prev == SOUTH)
	    || (_direction == SOUTH && prev == NORTH)
	    || (_direction == WEST && prev == EAST)
	    || (_direction == EAST && prev == WEST)) {
		_reachPrev = true;
	}
	if (_direction == WEST)
		_pacman.first -= 1;
	if (_direction == EAST)
		_pacman.first += 1;
	if (_direction == SOUTH)
		_pacman.second += 1;
	if (_direction == NORTH)
		_pacman.second -= 1;
	if (_pacman.first < 0)
		_pacman.first = _map[0].size() - 1;
	if (_pacman.first > static_cast<int>(_map[0].size() - 1))
		_pacman.first = 0;
}

void Pacman::mini_move()
{
	if (!check_move())
		return;
	if (_direction == WEST)
		_entities[0].second.first -= 0.1;
	if (_direction == EAST)
		_entities[0].second.first += 0.1;
	if (_direction == SOUTH)
		_entities[0].second.second += 0.1;
	if (_direction == NORTH)
		_entities[0].second.second -= 0.1;
}

std::pair<int, int> Pacman::directionInverted()
{
	if (_pacman.second > 0 and _pacman.second <= 14 and _pacman.first > 0
	    and _pacman.first < 15) {
		return {25, 29};
	}
	if (_pacman.second > 0 and _pacman.second <= 14 and _pacman.first > 15
	    and _pacman.first < 28) {
		return {1, 28};
	}
	if (_pacman.second > 14 and _pacman.second <= 31 and _pacman.first > 0
	    and _pacman.first < 15)
		return {25, 1};
	if (_pacman.second > 14 and _pacman.second <= 31 and _pacman.first > 15
	    and _pacman.first < 28)
		return {1, 1};
	return {1, 1};
}

void Pacman::Strong()
{

	if (_ghost1.getPos() == _pacman)
		_ghost1.setGoBack(true);
	if (_ghost2.getPos() == _pacman)
		_ghost2.setGoBack(true);
	if (_ghost3.getPos() == _pacman)
		_ghost3.setGoBack(true);
	_ghost1.Breadth(directionInverted(), _map);
	_ghost2.Breadth(directionInverted(), _map);
	_ghost3.Breadth(directionInverted(), _map);
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _power)
		    .count()
	    >= 10000) {
		_entities[1].first = 'G';
		_entities[2].first = 'G';
		_entities[3].first = 'G';
		_strong = false;
	}
}

void Pacman::init()
{
	_key = KEY_LEFT;
	_start = std::chrono::high_resolution_clock::now();
	_miniStart = std::chrono::high_resolution_clock::now();
	_miniStartIA = std::chrono::high_resolution_clock::now();
	_startMoving = std::chrono::high_resolution_clock::now();
	_reachPrev = false;
	_direction = WEST;
	_pacman = std::make_pair(13, 17);
	_strong = false;
	_ghost1 = Ghost(13, 13, WEST);
	_ghost2 = Ghost(12, 13, EAST);
	_ghost3 = Ghost(11, 13, WEST);
	_map.clear();
	loadMap();
	if (_speed != 100)
		_speed -= 100;
}

bool Pacman::checkWin()
{
	for (auto y : _map)
		for (auto x : y) {
			if (x == '.' or x == '@')
				return false;
		}
	return true;
}

void Pacman::tick()
{
	_start = std::chrono::high_resolution_clock::now();
	_miniStart = std::chrono::high_resolution_clock::now();
	move_key();
	if (checkWin())
		init();
	if (_strong == true)
		Strong();
	else {
		if (_ghost1.getPos() == _pacman)
			_status = LOSE;
		if (_ghost2.getPos() == _pacman)
			_status = LOSE;
		if (_ghost3.getPos() == _pacman)
			_status = LOSE;
		_ghost1.Breadth(_pacman, _map);
		_ghost2.Random(_map);
		_ghost3.Random(_map);
	}
	if (_map[_pacman.second][_pacman.first] == '@') {
		_map[_pacman.second][_pacman.first] = ' ';
		_strong = true;
		_entities[1].first = 'g';
		_entities[2].first = 'g';
		_entities[3].first = 'g';
		_power = std::chrono::high_resolution_clock::now();
	}
	if (_map[_pacman.second][_pacman.first] == '.') {
		_map[_pacman.second][_pacman.first] = ' ';
		_score += 1;
	}
	_entities[0].second.first = _pacman.first;
	_entities[0].second.second = _pacman.second;
}


void Pacman::play()
{
	if (checkWin())
		init();
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _start)
		    .count()
	    >= _speed) {
		tick();
	}
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _miniStart)
			    .count()
		    >= _speed / 10
	    && check_move()) {
		_miniStart = std::chrono::high_resolution_clock::now();
		mini_move();
	}
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _miniStartIA)
		    .count()
	    >= _speed / 10) {
		_miniStartIA = std::chrono::high_resolution_clock::now();
		_ghost1.miniMove(_entities[1]);
		_ghost2.miniMove(_entities[2]);
		_ghost3.miniMove(_entities[3]);
	}
	if (std::chrono::duration<double, std::milli>(
		    std::chrono::high_resolution_clock::now() - _startMoving)
		    .count()
	    >= 10000) {
		_ghost1.start();
		_ghost2.start();
		_ghost3.start();
	}
}
} // namespace arcade
