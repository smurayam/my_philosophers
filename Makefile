# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smurayam <smurayam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 16:14:32 by smurayam          #+#    #+#              #
#    Updated: 2026/02/11 16:16:08 by smurayam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

SRC_DIR     = srcs
OBJ_DIR     = objs
INC_DIR     = includes

SRC_FILES   = main.c \
              init.c \
              threads.c \
              routine.c \
              monitor.c \
              actions.c \
              utils.c \
              cleanup.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLUDES    = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re