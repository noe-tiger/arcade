##
## EPITECH PROJECT, 2017
## arcade
## File description:
## makefile
##

DEST_DIR	= ../

NAME		= $(DEST_DIR)arcade

CXX		= clang++

SRCS		:= src/main.cpp
SRCS		+= src/Core.cpp
SRCS		+= src/Exceptions.cpp

OBJS		:= $(SRCS:.cpp=.o)
DEPS		:= $(SRCS:.cpp=.d)

RM		= rm -f

LIBS		+= -ldl

CXXFLAGS		= -std=c++14
CXXFLAGS		+= -Wall -Wextra
CXXFLAGS		+= -I include
# Uncomment this flag for debug
CXXFLAGS		+= -g3

GREEN			= \033[0;32m
NO_COLOR		= \033[0m

%.o : %.cpp
	@$ $(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "$(CXX) $(CXXFLAGS) -x $< -o $@ [$(GREEN)OK$(NO_COLOR)]"

.SUFFIXES: .o .cpp

all: $(NAME)

$(NAME):$(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@
	@echo -e "$(CXX) $(OBJS) $(LIBS) -o $@[$(GREEN)LINKING OK$(NO_COLOR)]"

clean:
	@echo -e "$(GREEN)Cleaning up...$(NO_COLOR)"
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
