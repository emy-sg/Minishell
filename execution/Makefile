
NAME = execution.a

FLAG = -Wall -Wextra -Werror

LIB = util/*.o init/*.o src/cmd/*.o src/cd/*.o src/env/*.o src/export/*.o\
		src/pwd/*.o src/unset/*.o src/utils/*.o src/echo/*.o\
		src/exit/*.o src/other/*.o redirection/*.o

all: util_all src_all $(NAME)

$(NAME): $(MAIN)
	@ar -rc $(NAME) $(LIB)

clean: util_clean src_clean
	@rm -fr execution.dSYM

fclean: util_fclean src_fclean clean
	@rm -f $(NAME)

re: util_re src_re fclean all

src_all:
	@make -C init
	@make -C src/cd
	@make -C src/cmd
	@make -C src/env
	@make -C src/export
	@make -C src/pwd
	@make -C src/unset
	@make -C src/utils
	@make -C src/echo
	@make -C src/exit
	@make -C src/other
	@make -C redirection
src_clean:
	@make clean -C init
	@make clean -C src/cd
	@make clean -C src/cmd
	@make clean -C src/env
	@make clean -C src/export
	@make clean -C src/pwd
	@make clean -C src/unset
	@make clean -C src/utils
	@make clean -C src/echo
	@make clean -C src/exit
	@make clean -C src/other
	@make clean -C redirection
src_fclean:
	@make fclean -C init
	@make fclean -C src/cd
	@make fclean -C src/cmd
	@make fclean -C src/env
	@make fclean -C src/export
	@make fclean -C src/pwd
	@make fclean -C src/unset
	@make fclean -C src/utils
	@make fclean -C src/echo
	@make fclean -C src/exit
	@make fclean -C src/other
	@make fclean -C redirection
src_re:
	@make re -C init
	@make re -C src/cd
	@make re -C src/cmd
	@make re -C src/env
	@make re -C src/export
	@make re -C src/pwd
	@make re -C src/unset
	@make re -C src/utils
	@make re -C src/echo
	@make re -C src/exit
	@make re -C src/other
	@make re -C redirection


util_all:
	@make -C util
util_clean:
	@make clean -C util
util_fclean:
	@make fclean -C util
util_re:
	@make re -C util