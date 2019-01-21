//
// EPITECH PROJECT, 2018
// arcade
// File description:
// snake game
//

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <tuple>
#include <chrono>
#include "IGames.hpp"

#define SNAKE_HEAD 'X'
#define SNAKE_BODY 'O'
#define SNAKE_TAIL 'o'
#define WALL '#'
#define APPLE '@'
#define EMPTY ' '

const std::string
	MAP("###################\n\
#                 #\n\
# ### # ### # ### #\n\
# ### #     # ### #\n\
# ### # # # # ### #\n\
#     # # # #     #\n\
# ##### # # ##### #\n\
# #             # #\n\
# # ##### ##### # #\n\
#                 #\n\
# ##### ### ##### #\n\
#       # #       #\n\
# ### # ### # ### #\n\
# ### #     # ### #\n\
# ### # ### # ### #\n\
#     # # # #     #\n\
# ##### ### ##### #\n\
#                 #\n\
###################");


enum direction_e { NORTH, EAST, SOUTH, WEST };

constexpr direction_e DIRECTION[4] = {NORTH, EAST, SOUTH, WEST};
std::string LUL[] = {"NORTH", "EAST", "SOUTH", "WEST"};


namespace arcade {
class Snake : public IGame {
      public:
	Snake();
	~Snake() = default;
	void sendKey(int key);
	void play();
	const std::vector<std::vector<uint16_t>> &getMap() const;
	const entities_t &getEntities() const;
	status_e getStatus() const;
	int getScore() const;

      private:
	int countApple();
	void getFreeSpace();
	void removeSnake();
	void moveSnake();
	void putSnake();
	void setApple();
	void move_key();
	int _key;
	status_e _status = PLAYING;
	void loadMap();
	std::chrono::_V2::system_clock::time_point _start;
	entities_t _entities;
	std::vector<std::vector<uint16_t>> _map;
	std::vector<std::pair<int, int>> _snake;
	std::pair<int, int> _head;
	std::vector<std::pair<int, int>> _freeSpace;
	std::vector<std::pair<int, int>> _apple;
	int _score;
};
extern "C" IGame *create_game();
} // namespace arcade

#endif // SNAKE_HPP
