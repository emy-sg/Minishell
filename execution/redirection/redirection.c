#include "../../minishell.h"

int	last_redir(t_redir **redir)
{
	int	i;

	i = 0;
	while (redir[i])
		i++;
	return (i - 1);	
}

int	redirection(t_ast *s_ast)
{
	int last_redir_index;
	int	fd;

	last_redir_index = last_redir(s_ast->redir);
	fd = 0;
	if (s_ast->redir[last_redir_index]->type == OVERWRITE_REDIR)
		fd = open(s_ast->redir[last_redir_index]->file_name, O_RDWR | O_CREAT);
	if (fd == -1)
		return (sys_error(s_ast->argv[0], s_ast->redir[last_redir_index]->file_name));
	return (fd);
}