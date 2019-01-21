//
// EPITECH PROJECT, 2018
// arcade
// File description:
// ncurse interface
//

#include <curses.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Ncurse.hpp"

namespace arcade {
static const std::string getScore()
{
	std::string line;
	std::string lastLine;
	std::ifstream file;

	file.open("score.dat");
	if (file.is_open()) {
		while (getline(file, line))
			if (line.size() > 0)
				lastLine = line;
		file.close();
	}
	return lastLine;
}

Ncurse::Ncurse()
{
	if (!initscr() or curs_set(0) == ERR or noecho() == ERR
	    or ungetch(1) == ERR or keypad(stdscr, true) == ERR) {
		std::cerr << "Error : unable to start ncurses screen"
			  << std::endl;
		exit(84);
	}
	timeout(100);
	_isOpen = true;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	_game = "";
	_nickname = "";
	_lib = "";
}

std::string Ncurse::getGame() const
{
	return (_game);
}

std::string Ncurse::getNickName() const
{
	return (_nickname);
}

std::string Ncurse::getLib() const
{
	return (_lib);
}

Ncurse::~Ncurse()
{
	endwin();
	_isOpen = false;
}

int Ncurse::getKey()
{
	int ch = getch();

	if (ch == 27) {
		_isOpen = false;
		endwin();
	}
	return (ch);
}

static int set_square_size(int &lines, int &cols,
			   const std::vector<std::vector<uint16_t>> &map)
{
	int val = 1;

	while (LINES > static_cast<int>(map.size() * (val + 1))
	       && COLS > static_cast<int>(map[0].size()) * (val + 1))
		val += 1;
	lines = (LINES / 2) - ((map.size() / 2) * val);
	cols = (COLS / 2) - ((map[0].size() / 2) * val);
	return (val);
}

int Ncurse::draw_dot(std::vector<std::vector<uint16_t>> map, int i, int j)
{
	int lines;
	int cols;
	int val = set_square_size(lines, cols, map);

	if (map[i][j] == '#')
		attron(COLOR_PAIR(std::rand() % 8));
	for (int _i = 0; _i < val; _i++)
		for (int _j = 0; _j < val; _j++)
			mvprintw(i * val + lines + _i, j * val + cols + _j,
				 "%c", map[i][j]);
	attron(COLOR_PAIR(6));
	return (0);
}

int Ncurse::draw_dot(std::vector<std::vector<uint16_t>> map, char c, int i,
		     int j)
{
	int lines;
	int cols;
	int val = set_square_size(lines, cols, map);

	if (c == '#')
		attron(COLOR_PAIR(std::rand() % 8));
	for (int _i = 0; _i < val; _i++)
		for (int _j = 0; _j < val; _j++)
			mvprintw(i * val + lines + _i, j * val + cols + _j,
				 "%c", c);
	attron(COLOR_PAIR(6));
	return (0);
}

int Ncurse::displayMap(std::vector<std::vector<uint16_t>> map,
		       entities_t entities)
{
	clear();
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = 0; j < map[i].size(); j++)
			draw_dot(map, i, j);
	for (unsigned int i = 0; i < entities.size(); i++)
		draw_dot(map, entities[i].first, entities[i].second.second,
			 entities[i].second.first);
	refresh();
	return (0);
}

int Ncurse::update_name(int ch, std::string &name)
{
	if (ch == 27)
		_isOpen = false;
	if (isprint(ch))
		name.push_back(ch);
	else if (ch == KEY_BACKSPACE && name.size() > 0)
		name.pop_back();
	return (0);
}

void draw_square()
{
	for (int i = 0; i < COLS; i++) {
		mvprintw(0, i, "~");
		mvprintw(LINES - 1, i, "~");
	}
	for (int i = 0; i < LINES; i++) {
		mvprintw(i, 0, "|");
		mvprintw(i, COLS - 1, "|");
		if (i == 0 || i == LINES - 1) {
			mvprintw(i, 0, "*");
			mvprintw(i, COLS - 1, "*");
		}
	}
}

void draw_title()
{
	if (LINES < 10 && COLS < 50)
		return;
	attron(COLOR_PAIR(std::rand() % 6));
	mvprintw((LINES / 5), (COLS / 2) - 20, "%s",
		 "   __    ____   ___    __    ____  ____ ");
	attron(COLOR_PAIR(std::rand() % 6));
	mvprintw((LINES / 5) + 1, (COLS / 2) - 20, "%s",
		 "  /__\\  (  _ \\ / __)  /__\\  (  _ \\( ___)");
	attron(COLOR_PAIR(std::rand() % 6));
	mvprintw((LINES / 5) + 2, (COLS / 2) - 20, "%s",
		 " /(__)\\  )   /( (__  /(__)\\  )(_) ))__) ");
	attron(COLOR_PAIR(std::rand() % 6));
	mvprintw((LINES / 5) + 3, (COLS / 2) - 20, "%s",
		 "(__)(__)(_)\\_) \\___)(__)(__)(____/(____)");
	attron(COLOR_PAIR(7));
}

int Ncurse::print_option(const std::vector<std::string> &games,
			 const std::vector<std::string> &lib, bool choose,
			 int pos)
{
	int line = (LINES / 2) + pos;
	int cols = (!choose ? 7 : 57);

	mvprintw((LINES / 2) - 1, 7, "game :");
	for (unsigned int i = 0; i < games.size(); i++)
		mvprintw((LINES / 2) + i, 7, "%c  %s",
			 (games[i] == _game ? '*' : ' '), games[i].c_str());
	mvprintw((LINES / 2) - 1, 57, "library :");
	for (unsigned int i = 0; i < lib.size(); i++)
		mvprintw((LINES / 2) + i, 57, "%c  %s",
			 (lib[i] == _lib ? '*' : ' '), lib[i].c_str());
	mvprintw(line, cols, "->");
	mvprintw((LINES / 3) * 2, 10, "nickname : %s", _nickname.c_str());
	mvprintw((LINES / 3) * 2, 30, "score : %s", getScore().c_str());
	!choose ? _game = games[pos] : _lib = lib[pos];
	return (0);
}

int Ncurse::bioutifoul_term(const std::vector<std::string> &games,
			    const std::vector<std::string> &lib, int ch)
{
	static bool choose = 0;
	static int pos = 0;
	unsigned int max;

	draw_title();
	draw_square();

	if (ch == KEY_RIGHT || ch == KEY_LEFT)
		choose ? choose = false : choose = true;
	max = !choose ? games.size() : lib.size();
	if (ch == KEY_UP)
		pos == 0 ? pos = 0 : pos -= 1;
	else if (ch == KEY_DOWN)
		pos < static_cast<int>(max) - 1 ? pos += 1 : pos = max - 1;
	if (pos > static_cast<int>(max) - 1)
		pos = max - 1;
	print_option(games, lib, choose, pos);
	return (0);
}

int Ncurse::menu(const std::vector<std::string> &games,
		 const std::vector<std::string> &lib)
{
	int ch = 0;

	_isOpen = true;
	_game = games[0];
	_lib = lib[0];
	clear();
	while (ch != '\n' && _isOpen) {
		ch = getKey();
		if (ch != -1)
			clear();
		update_name(ch, _nickname);
		bioutifoul_term(games, lib, ch);
	}
	if (_nickname == "")
		_nickname = "BLANK";
	return (0);
}

bool Ncurse::isOpen() const
{
	return (_isOpen);
}

extern "C" IGraphical *create_object()
{
	return new Ncurse;
}
} // namespace arcade
