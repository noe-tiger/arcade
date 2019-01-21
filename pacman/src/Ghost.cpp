//
// EPITECH PROJECT, 2018
// arcade
// File description:
// ghost
//

#include <iostream>
#include "Ghost.hpp"

namespace arcade {
Ghost::Ghost(int x, int y, direction_e direction)
	: _pos({x, y})
	, _direction(direction)
	, _time(0)
	, _goBack(false)
	, _start(false)
	, _getOut(false)
{
}

static t_element *newElement(const int x, const int y, t_element *prev)
{
	t_element *new_element = new t_element;

	new_element->x = x;
	new_element->y = y;
	new_element->node_1 = nullptr;
	new_element->node_2 = nullptr;
	new_element->node_3 = nullptr;
	new_element->prev = prev;
	return new_element;
}

void Ghost::addNode(const int x, const int y, t_element *p)
{
	if (p->node_1 == nullptr) {
		_openList.push_back(newElement(x, y, p));
		p->node_1 = _openList.back();
	}
	else if (p->node_2 == nullptr) {
		_openList.push_back(newElement(x, y, p));
		p->node_2 = _openList.back();
	}
	else if (p->node_3 == nullptr) {
		_openList.push_back(newElement(x, y, p));
		p->node_3 = _openList.back();
	}
	if (x == _pacman.first and y == _pacman.second) {
		_openList.push_back(newElement(x, y, p));
		_end = _openList.back();
	}
	_fakeMap[y][x] = '0';
}

void Ghost::start()
{
	if (!_start) {
		_start = true;
		_getOut = true;
	}
}


void Ghost::Random(const std::vector<std::vector<uint16_t>> &_map)
{
	if (!_start)
		return;
	std::vector<std::pair<direction_e, std::pair<int, int>>> way;
	if (_goBack or _getOut) {
		Breadth({0, 0}, _map);
		return;
	}
	if (_pos.first - 1 < 0) {
		way.push_back({WEST, {_map[0].size() - 1, _pos.second}});
	}
	if (_pos.first + 1 > static_cast<int>(_map[0].size() - 1)) {
		way.push_back({EAST, {0, _pos.second}});
	}
	if (_direction != EAST and _pos.first - 1 >= 0
	    and _map[_pos.second][_pos.first - 1] != '#') {
		way.push_back({WEST, {_pos.first - 1, _pos.second}});
	}
	if (_direction != WEST
	    and _pos.first + 1 < static_cast<int>(_map[0].size() - 1)
	    and _map[_pos.second][_pos.first + 1] != '#') {
		way.push_back({EAST, {_pos.first + 1, _pos.second}});
	}
	if (_direction != SOUTH and _map[_pos.second - 1][_pos.first] != '#') {
		way.push_back({NORTH, {_pos.first, _pos.second - 1}});
	}
	if (_direction != NORTH and _map[_pos.second + 1][_pos.first] != '#') {
		way.push_back({SOUTH, {_pos.first, _pos.second + 1}});
	}
	if (way.size() == 0) {
		return;
	}
	auto choice = way[0 + rand() % ((way.size()) - 0)];
	_direction = choice.first;
	_pos = choice.second;
}

void Ghost::miniMove(std::pair<char, std::pair<float, float>> &entitie)
{
	_time = 0;
	if (entitie.second.first - _pos.first < 0)
		entitie.second.first += 0.1;
	if (entitie.second.first - _pos.first > 0)
		entitie.second.first -= 0.1;
	if (entitie.second.second - _pos.second < 0)
		entitie.second.second += 0.1;
	if (entitie.second.second - _pos.second > 0)
		entitie.second.second -= 0.1;
}

void Ghost::setGoBack(bool goBack)
{
	_goBack = goBack;
}

void Ghost::Breadth(const std::pair<int, int> &coord,
		    const std::vector<std::vector<uint16_t>> &map)
{
	if (!_start)
		return;
	if (_getOut) {
		_getOut = false;
		_pos = {13, 11};
		return;
	}
	if (_goBack) {
		_goBack = false;
		Breadth({13, 14}, map);
		_goBack = true;
		if (_pos.first == 13 and _pos.second == 14) {
			_goBack = false;
			_getOut = true;
		}
		return;
	}
	_fakeMap = map;
	_pacman = coord;
	_openList.push_back(newElement(_pos.first, _pos.second, nullptr));
	_fakeMap[_pos.second][_pos.first] = '0';
	_end = nullptr;
	while (!_openList.empty()) {
		int x = _openList.front()->x;
		int y = _openList.front()->y;
		if (x + 1 != (int)_fakeMap[y].size()
		    and _fakeMap[y][x + 1] != '#'
		    and _fakeMap[y][x + 1] != '0') {
			addNode(x + 1, y, _openList.front());
		}
		if (x - 1 > 0 and _fakeMap[y][x - 1] != '#'
		    and _fakeMap[y][x - 1] != '0') {
			addNode(x - 1, y, _openList.front());
		}
		if (y + 1 != (int)_fakeMap.size() and _fakeMap[y + 1][x] != '#'
		    and _fakeMap[y + 1][x] != '0') {
			addNode(x, y + 1, _openList.front());
		}
		if (y - 1 > 0 and _fakeMap[y - 1][x] != '#'
		    and _fakeMap[y - 1][x] != '0') {
			addNode(x, y - 1, _openList.front());
		}
		if (_end) {
			break;
		}
		_openList.erase(_openList.begin());
	}
	t_element *path = _end;
	if (path and path->prev == nullptr) {
		_pos.first = path->x;
		_pos.second = path->y;
		return;
	}
	while (path) {
		if (path->prev->prev == nullptr) {
			_pos.first = path->x;
			_pos.second = path->y;
			break;
		}
		_fakeMap[path->y][path->x] = 'M';
		path = path->prev;
	}
	while (!_openList.empty()) {
		delete _openList.front();
		_openList.erase(_openList.begin());
	}
}
} // namespace arcade
