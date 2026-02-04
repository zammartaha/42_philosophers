# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 11:29:26 by tzammar           #+#    #+#              #
#    Updated: 2026/02/04 20:13:44 by tzammar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread
AR      := ar rcs
RM      := rm -f

SRCS	:= philo.c ft_atoi.c routine.c utils.c monitor.c
OBJS	:= $(SRCS:.c=.o)
NAME	:= philo

all: $(NAME)

$(NAME): $(OBJS)
	@echo "--- Linking executable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "--- Executable $(NAME) successfully created."

%.o: %.c
	@echo "--- Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "--- Removing object files..."
	$(RM) $(OBJS)

fclean: clean
	@echo "--- Removing executable $(NAME)..."
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
