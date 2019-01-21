//
// EPITECH PROJECT, 2018
// arcade
// File description:
// ncurse interface
//

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include <cstdint>

#include "IGraphical.hpp"

namespace arcade {
class Ncurse : public IGraphical {
      public:
	Ncurse();
	std::string getGame() const;
	std::string getNickName() const;
	std::string getLib() const;
	int getKey();
	int displayMap(std::vector<std::vector<uint16_t>> map,
		       entities_t entities);
	int menu(const std::vector<std::string> &games,
		 const std::vector<std::string> &lib);
	bool isOpen() const;
	~Ncurse();

      protected:
	int check_arrows(unsigned int &pos, unsigned int &size, const int ch);
	int update_name(int ch, std::string &name);
	int bioutifoul_term(const std::vector<std::string> &games,
			    const std::vector<std::string> &lib, int ch);
	int print_option(const std::vector<std::string> &games,
			 const std::vector<std::string> &lib, bool choose,
			 int pos);
	int draw_dot(std::vector<std::vector<uint16_t>> map, int i, int j);
	int draw_dot(std::vector<std::vector<uint16_t>> map, char c, int i, int j);

	bool _isOpen;
	std::string _game;
	std::string _nickname;
	std::string _lib;
};
extern "C" IGraphical *create_object();
} // namespace arcade

#endif /* !NCURSE_HPP_ */
