##
## EPITECH PROJECT, 2017
## arcade
## File description:
## makefile
##

NCURSE_DIR	= ncurse
SFML_DIR	= sfml
SDL_DIR		= sdl
VULKAN_DIR	= vulkan
CORE_DIR	= core

SNAKE_DIR	= snake
PACMAN_DIR	= pacman

MAKE		= make -C

RM		= rm -f

all: core graphicals games

clean:
	@echo -e "$(GREEN)"Cleaning up..." $(NO_COLOR)"

fclean: clean
	$(MAKE) $(NCURSE_DIR) fclean
	$(MAKE) $(SFML_DIR) fclean
	$(MAKE) $(SDL_DIR) fclean
	$(MAKE) $(CORE_DIR) fclean
	$(MAKE) $(SNAKE_DIR) fclean
	$(MAKE) $(PACMAN_DIR) fclean

re: fclean all

core:
	$(MAKE) $(CORE_DIR)

graphicals:
	$(MAKE) $(NCURSE_DIR)
	$(MAKE) $(SFML_DIR)
	# $(MAKE) $(SDL_DIR)

games:
	$(MAKE) $(SNAKE_DIR)
	$(MAKE) $(PACMAN_DIR)

.PHONY: all clean fclean re core graphicals games
