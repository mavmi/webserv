NAME		=	webserv

HDRS_DIR		=	include
HDRS_CONFIG_DIR	=	$(HDRS_DIR)/configurations

SRCS_DIR		=	srcs
SRCS_UTILS_DIR	=	$(SRCS_DIR)/utils
SRCS_CONFIG_DIR	=	$(SRCS_DIR)/configurations
TEST_DIR		=	test

SRCS		=	$(addprefix $(SRCS_DIR)/, main.cpp)\
					$(addprefix $(SRCS_UTILS_DIR)/, utils_1.cpp)\
					$(addprefix $(SRCS_CONFIG_DIR)/, configuration_1.cpp configuration.cpp configuration_host.cpp exceptions.cpp route_configuration.cpp server_configuration.cpp utils.cpp)
HDRS		=	$(addprefix $(HDRS_DIR)/, utils.hpp)\
					$(addprefix $(HDRS_CONFIG_DIR)/, configuration_host.hpp	configuration.hpp exceptions.hpp route_configuration.hpp server_configuration.hpp utils.hpp)\
					$(addprefix $(TEST_DIR)/, test.hpp test_configuration.hpp)
OBJS		=	$(SRCS:.cpp=.o)
DEPEN		=	$(SRCS:.cpp=.d)

CC			=	g++
GCC			=	$(CC) -Wall -Wextra -Werror -std=c++98 -MMD -g -fsanitize=undefined -fsanitize=address

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
