NAME = minishell

FLAG = -Wall -Wextra -Werror -g -fsanitize=address

MAKE = make -C

all : $(NAME)

$(NAME):
	@$(MAKE) parsing/libft
	@$(MAKE) parsing/lexer
	@$(MAKE) parsing/parser
	@$(MAKE) execution
	@gcc $(FLAG) execution/execution.a parsing/libft/libft.a parsing/lexer/lexer.a parsing/parser/parser.a main.c -lreadline -o $(NAME)

clean:
	@$(MAKE) parsing/libft clean
	@$(MAKE) parsing/lexer clean
	@$(MAKE) parsing/parser clean
	@$(MAKE) execution clean
	rm -rf main.o

fclean: clean
	@$(MAKE)  parsing/libft fclean
	@$(MAKE)  parsing/lexer fclean
	@$(MAKE)  parsing/parser fclean
	@$(MAKE) execution fclean
	rm -rf $(NAME)

re: fclean all