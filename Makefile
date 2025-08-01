# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 17:44:25 by wsilveir          #+#    #+#              #
#    Updated: 2025/07/31 17:45:00 by wsilveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
HDRS = get_next_line.h

SRCS = get_next_line_utils.c get_next_line.c

OBJS = $(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(FLAGS) -I $(HDRS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
