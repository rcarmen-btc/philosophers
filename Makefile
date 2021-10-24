# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/10/23 22:43:59 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC = main.h
SRC = main.c utils.c init_and_tools.c forks.c
OBJ = $(patsubst %.c, %.o, $(SRC))

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = od/

INC_PATH = $(addprefix $(INC_DIR), $(INC))
SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))
OBJ_PATH = $(addprefix $(OBJ_DIR), $(OBJ))

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g
OPT_FLUGS = -pipe

HMM_COLOR   = \033[1;95m
COM_COLOR   = \033[1;94m
OBJ_COLOR   = \033[1;96m
OK_COLOR    = \033[1;92m
ERROR_COLOR = \033[1;91m
WARN_COLOR  = \033[1;93m
NO_COLOR    = \033[0m

SYAN_COLOR = \e[1;96m
YELLOW_COLOR = \e[1;93m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

define run
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all: od $(NAME)

$(NAME): $(OBJ_PATH) $(INC_PATH)
	@$(call run, $(CC) $(CFLAGS) $(OPT_FLUGS) $(OBJ_PATH) -o $(NAME))
	@echo "$(OK_COLOR)----SUCCSESS PHILO----$(NO_COLOR)"

VPATH = $(SRC_DIR)

$(OBJ_DIR)%.o: %.c 
	@$(call run, $(CC) $(CFLAGS) $(OPT_FLUGS) -c $< -o $@ $(addprefix -I, $(INC_DIR)))
	
od:
	@mkdir -p od/

clean:
	@if [ -e $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR);	\
  		printf "%-60b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(OBJ_DIR)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	else \
  		printf "%-41b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(OBJ_DIR)" "$(ERROR_COLOR)[There is no such directory]$(NO_COLOR)\n"; \
	fi;

fclean: clean
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
  		printf "%-60b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	else \
  		printf "%-41b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(ERROR_COLOR)[There is no such file]$(NO_COLOR)\n"; \
	fi;

re: fclean all

.PHONY: all clean fclean re
