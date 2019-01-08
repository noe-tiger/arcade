##
## EPITECH PROJECT, 2017
## arcade
## File description:
## makefile
##

DEST_DIR	= ../lib/

NAME	= $(DEST_DIR)lib_arcade_sdl2.so

CXX	= clang++

SRCS	:= src/Sdl.cpp

OBJS	:= $(SRCS:.cpp=.o)
DEPS	:= $(SRCS:.cpp=.d)

LIBS	:= `pkg-config sdl2 --libs` -lSDL2_ttf -lSDL2_image

RM	= rm -f

CXXFLAGS	= -std=c++14 -fPIC
CXXFLAGS	+= -Werror -Wall -Wextra -Wno-switch
CXXFLAGS	+= -I../core/include -I./include
CXXFLAGS	+= `pkg-config --cflags sdl2`
CXXFLAGS	+= -g3

LDFLAGS		= -shared

GREEN		= \033[0;32m
NO_COLOR	= \033[0m

%.o : %.cpp
	@$ $(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "$(CXX) $(CXXFLAGS) -x $< -o $@ [$(GREEN)OK$(NO_COLOR)]"
.SUFFIXES: .o .cpp

-include $(OBJS:%.o=%.d)

all: $(NAME)

$(NAME):$(OBJS)
	@$ $(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -Wl,-z,defs -o $@
	@echo -e "$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -Wl$@ -o $@ \
	[$(GREEN)LINKING OK$(NO_COLOR)]"

clean:
	@echo -e "$(GREEN)Cleaning up...$(NO_COLOR)"
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
