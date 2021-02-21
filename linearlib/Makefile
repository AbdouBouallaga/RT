# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 19:50:48 by babdelka          #+#    #+#              #
#    Updated: 2021/01/29 15:29:35 by babdelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = linear_alg.a

SRC = ft_magnitude.c ft_normalize.c ft_negative.c ft_dotproduct.c \
	ft_crossproduct.c ft_vectoradd.c ft_vectorsub.c ft_vectormulti.c

CC = gcc

INC = linear_alg.h

CFLAG = -Wextra -Wall -Werror

EXEC = gcc $(CFLAG)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(EXEC) -c $(SRC)
	ar rc  $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
