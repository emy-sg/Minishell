#include "../../minishell.h"

int	redirection(t_ast *s_ast)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	while (s_ast->redir[i])
	{
		if (s_ast->redir[i]->type == OVERWRITE_REDIR)
			fd = open(s_ast->redir[i]->file_name, O_RDWR | O_CREAT, 0777);
		if (fd == -1)
			return (sys_error(s_ast->argv[0], s_ast->redir[i]->file_name));
		i++;
	}
	return (fd);
}