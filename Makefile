# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 18:29:03 by fcouserg          #+#    #+#              #
#    Updated: 2024/09/13 17:50:23 by fcouserg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	cc
INC			=	inc/
CFLAGS		=	-Wall -Wextra -Werror -I -pthread
DEP_FLAGS	:=	-MMD -MP
RM			=	rm -rf

PHILO	= main.c parsing.c threads.c init.c monitor.c utils.c

SRC_NAMES	= $(PHILO)

OBJ	= $(SRC_NAMES:.c=.o)
DEP	= $(SRC_NAMES:.c=.d)

%.o: %.c
	$(CC) $(DEP_FLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(DEP_FLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ) $(DEP)

fclean:		clean
			$(RM) $(NAME)

re:		fclean all 
			
.PHONY:	all clean fclean re 

-include $(DEP)