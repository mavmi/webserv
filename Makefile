NAME		=	webserv

SRCS_DIR	=	srcs
UTILS_DIR	=	$(SRCS_DIR)/utils
CONFIG_DIR	=	$(SRCS_DIR)/configurations
HDRS_DIR	=	include
TEST_DIR	=	test

SRCS		=	$(addprefix $(SRCS_DIR)/, main.cpp)\
					$(addprefix $(UTILS_DIR)/, utils_1.cpp)\
					$(addprefix $(CONFIG_DIR)/, configuration_1.cpp)
HDRS		=	$(addprefix $(HDRS_DIR)/, utils.hpp configuration.hpp)\
					$(addprefix $(TEST_DIR)/, test.hpp test_configuration.hpp)
OBJS		=	$(SRCS:.cpp=.o)
DEPEN		=	$(SRCS:.cpp=.d)

CC			=	g++
GCC			=	$(CC) -Wall -Wextra -Werror -std=c++98 -MMD -g

%.o:		%.cpp $(HDRS)
			$(GCC) -c -o $@ $<

all:		$(NAME)

$(NAME):	$(OBJS)
			$(GCC) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS) $(DEPEN)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include $(DEPEN)

.PHONY: all clean fclean re
