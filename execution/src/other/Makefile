# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 14:23:33 by emallah           #+#    #+#              #
#    Updated: 2021/11/04 17:22:38 by isghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = other.a

FLAG = -Wall -Wextra -Werror

FILE = other.c

$(NAME): $(FILE)
	@gcc $(FLAG)  -c $(FILE)
	@ar -rc $(NAME) *.o 
	
all : $(NAME)

clean:
	@rm -fr *.o

fclean: clean
	@rm -fr $(NAME)

re: fclean all
