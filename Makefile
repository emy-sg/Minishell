NAME = minishell

# FLAG = -Wall -Wextra -Werror -g -fsanitize=address
FLAG = -Wall -Wextra -Werror

EXECUTION = execution/*/*.c execution/*/*/*.c

PARSING = parsing/*/*.c

MAIN = main.c

all : $(NAME)

$(NAME): $(EXECUTION) $(PARSING)
	gcc $(FLAG) $(EXECUTION) $(PARSING) $(MAIN) -lreadline -o $(NAME)

clean: 
	rm -fr minishell.dSYM

fclean: clean
	rm -fr $(NAME)

re: fclean all