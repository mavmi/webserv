NAME		=	webserv
TEST_NAME	=	$(NAME)_test

#######################
### WEBSERV SOURCES ###
#######################

### .o & .d ###
TMP_FILES_DIR		=	tmp_files

### headers ###
HDRS_UTILS			=	container.hpp exceptions.hpp parser_abstract_parent.hpp utils.hpp wrapper.hpp
HDRS_CONFIG			=	configuration_host.hpp	configuration.hpp parser.hpp route_configuration.hpp server_configuration.hpp utils.hpp
HDRS_HTTP_HEADERS	=	common_headers.hpp general_headers.hpp headers_abstract_parent.hpp request_headers.hpp request_status_line.hpp response_headers.hpp response_status_line.hpp status_line_abstract_parent.hpp utils.hpp
HDRS_HTTP_REQ		=	http_request.hpp http_request_parser.hpp utils.hpp
HDRS_HTTP_RES		=	http_response_generator.hpp http_response.hpp utils.hpp

### sources ###
SRCS_UTILS			=	container.cpp exceptions.cpp parser_abstract_parent.cpp utils.cpp wrapper.cpp
SRCS_CONFIG			=	configuration.cpp configuration_host.cpp parser.cpp route_configuration.cpp server_configuration.cpp utils.cpp
SRCS_HTTP_HEADERS	=	common_headers.cpp general_headers.cpp headers_abstract_parent.cpp request_headers.cpp request_status_line.cpp response_headers.cpp response_status_line.cpp status_line_abstract_parent.cpp
SRCS_HTTP_REQ		=	http_request.cpp http_request_parser.cpp utils.cpp
SRCS_HTTP_RES		=	http_response_generator.cpp http_response.cpp

### objects ###
OBJS_UTILS			=	$(SRCS_UTILS:.cpp=.o)
OBJS_CONFIG			=	$(SRCS_CONFIG:.cpp=.o)
OBJS_HTTP_HEADERS	=	$(SRCS_HTTP_HEADERS:.cpp=.o)
OBJS_HTTP_REQ		=	$(SRCS_HTTP_REQ:.cpp=.o)
OBJS_HTTP_RES		=	$(SRCS_HTTP_RES:.cpp=.o)

### dependencies ###
DEPEN_UTILS			=	$(SRCS_UTILS:.cpp=.d)
DEPEN_CONFIG		=	$(SRCS_CONFIG:.cpp=.d)
DEPEN_HTTP_HEADERS	=	$(SRCS_HTTP_HEADERS:.cpp=.d)
DEPEN_HTTP_REQ		=	$(SRCS_HTTP_REQ:.cpp=.d)
DEPEN_HTTP_RES		=	$(SRCS_HTTP_RES:.cpp=.d)

### directories ###
HDRS_DIR			=	include
HDRS_UTILS_DIR		=	$(HDRS_DIR)/utils
HDRS_CONFIG_DIR		=	$(HDRS_DIR)/configurations
HDRS_HTTP_HEAD_DIR	=	$(HDRS_DIR)/http_headers
HDRS_HTTP_REQ_DIR	=	$(HDRS_DIR)/http_request_parser
HDRS_HTTP_RES_DIR	=	$(HDRS_DIR)/http_response_generator

SRCS_DIR			=	srcs
SRCS_UTILS_DIR		=	$(SRCS_DIR)/utils
SRCS_CONFIG_DIR		=	$(SRCS_DIR)/configurations
SRCS_HTTP_HEAD_DIR	=	$(SRCS_DIR)/http_headers
SRCS_HTTP_REQ_DIR	=	$(SRCS_DIR)/http_request_parser
SRCS_HTTP_RES_DIR	=	$(SRCS_DIR)/http_response_generator

### main.cpp ###
MAIN_SRC		=	$(SRCS_DIR)/main.cpp
MAIN_OBJ		=	$(addprefix $(TMP_FILES_DIR)/, $(MAIN_SRC:.cpp=.o))
MAIN_DEPEN		=	$(addprefix $(TMP_FILES_DIR)/, $(MAIN_SRC:.cpp=.d))

### result values ###
HDRS		=	$(addprefix $(HDRS_UTILS_DIR)/, $(HDRS_UTILS))\
					$(addprefix $(HDRS_CONFIG_DIR)/, $(HDRS_CONFIG))\
					$(addprefix $(HDRS_HTTP_HEAD_DIR)/, $(HDRS_HTTP_HEADERS))\
					$(addprefix $(HDRS_HTTP_REQ_DIR)/, $(HDRS_HTTP_REQ))\
					$(addprefix $(HDRS_HTTP_RES_DIR)/, $(HDRS_HTTP_RES))
SRCS		=	$(addprefix $(SRCS_UTILS_DIR)/, $(SRCS_UTILS))\
					$(addprefix $(SRCS_CONFIG_DIR)/, $(SRCS_CONFIG))\
					$(addprefix $(SRCS_HTTP_HEAD_DIR)/, $(SRCS_HTTP_HEADERS))\
					$(addprefix $(SRCS_HTTP_REQ_DIR)/, $(SRCS_HTTP_REQ))\
					$(addprefix $(SRCS_HTTP_RES_DIR)/, $(SRCS_HTTP_RES))
OBJS		=	$(addprefix $(TMP_FILES_DIR)/, $(SRCS:.cpp=.o))
DEPEN		=	$(addprefix $(TMP_FILES_DIR)/, $(SRCS:.cpp=.d))

####################
### TEST SOURCES ###
####################

### headers ###
TEST_HDRS_test	=	test.hpp test_utils.hpp

### sources ###
TEST_SRCS_test	=	test.cpp test_utils.cpp

### objects ###
TEST_OBJS_test	=	$(TEST_SRCS_test:.cpp=.o)

### dependencies ###
TEST_DEPEN_test	=	$(TEST_SRCS_test:.cpp=.d)

### directories ###
TEST_DIR		=	test

TEST_HDRS_DIR	=	$(TEST_DIR)/include
TEST_SRCS_DIR	=	$(TEST_DIR)/srcs

### main.cpp ###
TEST_MAIN		=	$(TEST_SRCS_DIR)/main.cpp
TEST_MAIN_OBJ	=	$(addprefix $(TMP_FILES_DIR)/, $(TEST_MAIN:.cpp=.o))
TEST_MAIN_DEPEN	=	$(addprefix $(TMP_FILES_DIR)/, $(TEST_MAIN:.cpp=.d))

### result values ###
TEST_HDRS	=	$(addprefix $(TEST_HDRS_DIR)/, $(TEST_HDRS_test))
TEST_SRCS	=	$(addprefix $(TEST_SRCS_DIR)/, $(TEST_SRCS_test))
TEST_OBJS	=	$(addprefix $(TMP_FILES_DIR)/, $(TEST_SRCS:.cpp=.o))
TEST_DEPEN	=	$(addprefix $(TMP_FILES_DIR)/, $(TEST_SRCS:.cpp=.d))


#############
### RULES ###
#############
CC			=	g++
GCC			=	$(CC) -Wall -Wextra -Werror -std=c++98 -MMD -g -fsanitize=undefined -fsanitize=address -fsanitize=leak


# $@					$<
$(TMP_FILES_DIR)/%.o:	%.cpp $(HDRS) $(TEST_HDRS)
						@mkdir -p $(dir $@)
						$(GCC) -c -o $@ $<

all:					$(NAME)

$(NAME):				$(OBJS) $(MAIN_OBJ)
						$(GCC) $(OBJS) $(MAIN_OBJ) -o $(NAME)

clean:			
						@rm -rf $(TMP_FILES_DIR)

fclean:					clean
						@rm -f $(NAME) $(TEST_NAME)

re:						fclean all

test:					$(OBJS) $(TEST_OBJS) $(TEST_MAIN_OBJ)
						@mkdir -p $(dir $@)
						$(GCC) $(OBJS) $(TEST_OBJS) $(TEST_MAIN_OBJ) -o $(TEST_NAME)

doNotForgetToDelete:
						$(eval wsrv_dir:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST)))))

						@echo '\033[0;31m' &&\
							grep -r --include "*.hpp" --include "*.cpp"\
								'[Н,н][Е,е]\s*[З,з][А,а][Б,б][Ы,ы][Т,т][Ь,ь]\s*[У,у][Д,д][А,а][Л,л][И,и][Т,т][Ь,ь]'\
							$(wsrv_dir);\
							echo '\033[0m'
			
-include $(DEPEN)

.PHONY: all clean fclean re test doNotForgetToDelete
