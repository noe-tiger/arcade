//
// EPITECH PROJECT, 2018
// "a"
// File description:
// a
//

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include <cstdint>
#include <vector>

class Pacman;

typedef struct s_element {
	int x;
	int y;
	struct s_element *node_1;
	struct s_element *node_2;
	struct s_element *node_3;
	struct s_element *prev;
} t_element;

enum direction_e { NORTH, EAST, SOUTH, WEST };

namespace arcade {
class Ghost {
      public:
	Ghost(int x, int y, direction_e direction);
	~Ghost()
	{
	}
	void addNode(const int x, const int y, t_element *p);
	std::pair<int, int> getPos() const
	{
		return _pos;
	}
	void setGoBack(bool goBack);
	void Breadth(const std::pair<int, int> &coord,
		     const std::vector<std::vector<uint16_t>> &map);
	void Random(const std::vector<std::vector<uint16_t>> &coord);
	void miniMove(std::pair<char, std::pair<float , float >> &entitie);
	void start();

      private:
	std::pair<int, int> _pos;
	direction_e _direction;
	std::vector<t_element *> _openList;
	std::pair<int, int> _pacman;
	t_element *_end;
	std::vector<std::vector<uint16_t>> _fakeMap;
	int _time;
	bool _goBack;
	bool _start;
	bool _getOut;
};
} // namespace arcade

#endif // GHOST_HPP
