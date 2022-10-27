NAME		=	webserv
TEST_NAME	=	$(NAME)_test

#######################
### WEBSERV SOURCES ###
#######################
HDRS_DIR		=	include
HDRS_CONFIG_DIR	=	$(HDRS_DIR)/configurations

SRCS_DIR		=	srcs
SRCS_UTILS_DIR	=	$(SRCS_DIR)/utils
SRCS_CONFIG_DIR	=	$(SRCS_DIR)/configurations

MAIN_SRC	=	$(SRCS_DIR)/main.cpp
MAIN_OBJ	=	$(MAIN_SRC:.cpp=.o)
MAIN_DEPEN	=	$(MAIN_SRC:.cpp=.d)

SRCS		=	$(addprefix $(SRCS_UTILS_DIR)/, utils_1.cpp)\
					$(addprefix $(SRCS_CONFIG_DIR)/, configuration.cpp configuration_host.cpp exceptions.cpp route_configuration.cpp server_configuration.cpp utils.cpp)
HDRS		=	$(addprefix $(HDRS_DIR)/, utils.hpp)\
					$(addprefix $(HDRS_CONFIG_DIR)/, configuration_host.hpp	configuration.hpp exceptions.hpp route_configuration.hpp server_configuration.hpp utils.hpp)
OBJS		=	$(SRCS:.cpp=.o)
DEPEN		=	$(SRCS:.cpp=.d)

####################
### TEST SOURCES ###
####################
TEST_DIR		=	test

TEST_HDRS_DIR	=	$(TEST_DIR)/include
TEST_SRCS_DIR	=	$(TEST_DIR)/srcs

TEST_MAIN		=	$(TEST_SRCS_DIR)/main.cpp
TEST_MAIN_OBJ	=	$(TEST_MAIN:.cpp=.o)
TEST_MAIN_DEPEN	=	$(TEST_MAIN:.cpp=.d)

TEST_SRCS		=	$(addprefix $(TEST_SRCS_DIR)/, test.cpp test_utils.cpp)
TEST_HDRS		=	$(addprefix $(TEST_HDRS_DIR)/, test.hpp test_utils.hpp)
TEST_OBJS		=	$(TEST_SRCS:.cpp=.o)
TEST_DEPEN		=	$(TEST_SRCS:.cpp=.d)

#############
### RULES ###
#############
CC			=	g++
GCC			=	$(CC) -Wall -Wextra -Werror -std=c++98 -MMD -g -fsanitize=undefined -fsanitize=address


%.o:		%.cpp $(HDRS) $(TEST_HDRS)
			$(GCC) -c -o $@ $<

all:		$(NAME)

$(NAME):	$(OBJS) $(MAIN_OBJ)
			$(GCC) $(OBJS) $(MAIN_OBJ) -o $(NAME)

clean:
			rm -f $(MAIN_OBJ) $(MAIN_DEPEN) $(OBJS) $(DEPEN) $(TEST_MAIN_OBJ) $(TEST_MAIN_DEPEN) $(TEST_OBJS) $(TEST_DEPEN)

fclean:		clean
			rm -f $(NAME) $(TEST_NAME)

re:			fclean all

test:		$(OBJS) $(TEST_OBJS) $(TEST_MAIN_OBJ)
			$(GCC) $(OBJS) $(TEST_OBJS) $(TEST_MAIN_OBJ) -o $(TEST_NAME)

-include $(DEPEN)

.PHONY: all clean fclean re
