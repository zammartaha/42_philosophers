# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 11:29:26 by tzammar           #+#    #+#              #
#    Updated: 2026/02/04 20:13:55 by tzammar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
LDLIBS  := -lpthread
AR      := ar rcs
RM      := rm -f

SRCS	:= ft_bonus.c monitor_bonus.c philo_bonus.c routine_bonus.c utils_bonus.c
OBJS	:= $(SRCS:.c=.o)
NAME	:= philo_bonus

all: $(NAME)

$(NAME): $(OBJS)
	@echo "--- Linking executable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
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
