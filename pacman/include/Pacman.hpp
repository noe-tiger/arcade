//
// EPITECH PROJECT, 2018
// arcade
// File description:
// snake game
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include <queue>
# include <tuple>
# include <chrono>

# include "IGames.hpp"
# include "Ghost.hpp"

# define SNAKE_HEAD 'X'
# define SNAKE_BODY 'O'
# define SNAKE_TAIL 'o'
# define WALL '#'
# define APPLE '@'
# define EMPTY ' '

const std::string
MAP("###########################\n\
#............##...........#\n\
#.####.#####.##.####.####.#\n\
#@####.#####.##.####.####@#\n\
#.####.#####.##.####.####.#\n\
#.........................#\n\
#.####.##.########.#.####.#\n\
#.####.##.########.#.####.#\n\
#......##....##....#......#\n\
######.#####.##.####.######\n\
     #.#####.##.####.#     \n\
     #.##         ##.#     \n\
     #.## ###  ## ##.#     \n\
######.## #     # ##.######\n\
......... #     # .........\n\
######.## #     # ##.######\n\
     #.## ####### ##.#     \n\
     #.##          #.#     \n\
     #.##.########.#.#     \n\
######.##.########.#.######\n\
#............##...........#\n\
#.####.#####.##.####.####.#\n\
#.####.#####.##.####.####.#\n\
#@...#...............#...@#\n\
####.#.##.########.#.#.####\n\
####.#.##.########.#.#.####\n\
#......##....##....#......#\n\
#.##########.##.#########.#\n\
#.##########.##.#########.#\n\
#.........................#\n\
###########################");




namespace arcade {
class Pacman : public IGame {
      public:
	Pacman();
	~Pacman() = default;
	void sendKey(int key);
	void play();
	const std::vector<std::vector<uint16_t>> &getMap() const;
	const entities_t &getEntities() const;
	status_e getStatus() const;
	int getScore() const;

      private:
	void Strong();
	bool checkWin();
	void init();
	std::pair<int, int> directionInverted();
	void move_key();
	void mini_move();
	int check_move();
	bool ReachPrev();
	int _key;
	status_e _status = PLAYING;
	void loadMap();
	void tick();
	std::chrono::_V2::system_clock::time_point _start;
	std::chrono::_V2::system_clock::time_point _miniStart;
	std::chrono::_V2::system_clock::time_point _miniStartIA;
	std::chrono::_V2::system_clock::time_point _power;
	std::chrono::_V2::system_clock::time_point _startMoving;
	std::vector<std::vector<uint16_t>> _map;
	bool _reachPrev;
	entities_t _entities;
	direction_e _direction;
	direction_e _prev;
	std::pair<int, int> _pacman;
	bool _strong;
	Ghost _ghost1;
	Ghost _ghost2;
	Ghost _ghost3;
	int _speed;
	int _score;
};
extern "C" IGame *create_game()
{
	return new Pacman;
}
} // namespace arcade


#endif // PACMAN_HPP_
