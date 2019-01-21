#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace arcade {
class Sprite : public sf::Sprite {
      public:
	Sprite(const std::string &pathname = "");
	bool setImage(const std::string &pathname);

      protected:
	sf::Texture _texture;
};
bool loadSprites(std::vector<Sprite> &sprites, const std::string &folder);
} // namespace arcade

#endif /* !SPRITE_HPP_ */
