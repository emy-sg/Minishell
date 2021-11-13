#include "../../minishell.h"

int	ft_redir(t_ast *s_ast, t_env_export *env_export)
{
	t_redirect *redirect;
	
	redirect = init_redirect(s_ast);
	if (redirect == NULL)
		return (ERROR);
	if (redirect->fdin != 0)
		simple_redir_in(redirect, s_ast);
	if (redirect->fdout != 0)
		simple_redir_out(redirect, s_ast);
	ft_cmd(s_ast, env_export);
	if (redirect->fdin != 0)
		redir_in_back_to_normal(redirect);
	if (redirect->fdout != 0)
		redir_out_back_to_normal(redirect);
	free(redirect);
	return (EXIT_SUCCESS);
}
