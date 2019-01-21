//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Igraphical interface
//

#ifndef IGRAPHICAL_HPP
#define IGRAPHICAL_HPP

#include <stdint.h>

#include <string>
#include <vector>
#include <tuple>

#define SNAKE_HEAD 'X'
#define SNAKE_BODY 'O'
#define SNAKE_TAIL 'o'
#define WALL '#'
#define APPLE '@'
#define EMPTY ' '
#define FOOD '.'
#define PACMAN "P"
#define GHOST "G"
#define EYES ":"
#define BLUE_GHOST "B"

using entities_t = std::vector<std::pair<char, std::pair<float, float>>>;

namespace arcade {
class IGraphical {
      public:
	virtual std::string getGame() const = 0;
	virtual std::string getNickName() const = 0;
	virtual std::string getLib() const = 0;
	virtual int getKey() = 0;
	virtual int displayMap(std::vector<std::vector<uint16_t>> map,
			       entities_t entities) = 0;
	virtual int menu(const std::vector<std::string> &games,
			 const std::vector<std::string> &libs) = 0;
	virtual bool isOpen() const = 0;
	virtual ~IGraphical() = default;

      private:
};
extern "C" IGraphical *create_object();
} // namespace arcade

#endif // IGRAPHICAL_HPP
