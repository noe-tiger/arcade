##
## EPITECH PROJECT, 2017
## arcade
## File description:
## makefile
##

DEST_DIR	= ../games/

NAME	= $(DEST_DIR)lib_arcade_nibbler.so

CXX	= clang++

SRCS	:= src/Snake.cpp
# x
OBJS	:= $(SRCS:.cpp=.o)
DEPS	:= $(SRCS:.cpp=.d)

RM	= rm -f

CXXFLAGS	= -std=c++14 -fPIC
CXXFLAGS	+= -Werror -Wall -Wextra
CXXFLAGS	+= -g3
CXXFLAGS	+= -I../core/include -I./include

LDFLAGS		= -shared -Wl,-z,defs

GREEN		= \033[0;32m
NO_COLOR	= \033[0m

%.o : %.cpp
	@$ $(CXX) $(CXXFLAGS) $(LIBS) -c $< -o $@
	@echo -e "$(CXX) $(CXXFLAGS) -x $< -o $@ [$(GREEN)OK$(NO_COLOR)]"
.SUFFIXES: .o .cpp

-include $(OBJS:%.o=%.d)

all: $(NAME)

$(NAME):$(OBJS)
	@$ $(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -Wl,-z,defs -o $@
	@echo -e "$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -Wl,-h$@ -o $@ \
	[$(GREEN)LINKING OK$(NO_COLOR)]"

clean:
	@echo -e "$(GREEN)Cleaning up...$(NO_COLOR)"
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
