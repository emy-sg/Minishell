#include "../../minishell.h"

int	simple_redir_in(t_redirect *redirect, t_ast *s_ast)
{
	if (ft_strcstr(s_ast->argv[0], "exit") == NULL)
	{
		if (dup2(redirect->fdin, STDIN_FILENO) < 0)
			return (sys_error(NULL, NULL));
	}
	return (EXIT_SUCCESS);
}

int	simple_redir_out(t_redirect *redirect, t_ast *s_ast)
{
	if (ft_strcstr(s_ast->argv[0], "exit") == NULL)
	{
		if (dup2(redirect->fdout, STDOUT_FILENO) < 0)
			return (sys_error(NULL, NULL));
	}
	return (EXIT_SUCCESS);
}
