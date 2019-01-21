//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Igraphical interface
//

#ifndef IGAME_HPP
#define IGAME_HPP

#include <stdint.h>

#include <string>
#include <vector>
#include <tuple>

using entities_t = std::vector<std::pair<char, std::pair<float, float>>>;

namespace arcade {
class IGame {
      public:
	enum status_e { PLAYING, WIN, LOSE };
	virtual ~IGame() = default;
	virtual void sendKey(int key) = 0;
	virtual void play() = 0;
	virtual const std::vector<std::vector<uint16_t>> &getMap() const = 0;
	virtual const entities_t &getEntities() const = 0;
	virtual int getScore() const = 0;
	virtual status_e getStatus() const = 0;

      private:
};
extern "C" IGame *create_game();
} // namespace arcade

#endif // IGAME_HPP
