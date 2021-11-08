NAME = redirection.a

FLAG = -Wall -Wextra -Werror

FILE = redirection.c

$(NAME): $(FILE)
	@gcc $(FLAG)  -c $(FILE)
	@ar -rc $(NAME) *.o
	
all: $(NAME)

clean:
	@rm -fr *.o

fclean: clean
	@rm -fr $(NAME)

re: fclean all
