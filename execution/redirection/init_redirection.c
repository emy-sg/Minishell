#include "../../minishell.h"

t_redirect	*init_redirect(t_ast *s_ast)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)ft_calloc(sizeof(t_redirect), 2);
	if (redirect == NULL)
	{
		sys_error(s_ast->argv[0], NULL);
		return (NULL);
	}
	redirect->stdout_fd = dup(1);
	redirect->stdin_fd = dup(0);
	redirect->fdin = 0;
	redirect->fdout = 0;
	open_files(s_ast, redirect);
	return (redirect);
}

void	open_files(t_ast *s_ast, t_redirect *redirect)
{
	int			i;

	i = 0;
	while (s_ast->redir[i])
	{
		if (s_ast->redir[i]->type == INPUT_REDIR || s_ast->redir[i]->type == HERE_DOC_REDIR)
			redirect->fdin = redir_fdin(s_ast->redir[i]);
		if (s_ast->redir[i]->type == OVERWRITE_REDIR || s_ast->redir[i]->type == APPEND_REDIR)
			redirect->fdout = redir_fdout(s_ast->redir[i]);
		if (redirect->fdin == -1 || redirect->fdout == -1)
		{
			g_status = 1;
			sys_error(NULL, s_ast->redir[i]->file_name);
		}
		i++;
	}
}

int	redir_fdin(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == INPUT_REDIR)
		fd = open(redir->file_name, O_RDONLY, 0777);
	if (redir->type == HERE_DOC_REDIR)
		fd = here_doc(redir->file_name);
	return (fd);
}

int	redir_fdout(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == OVERWRITE_REDIR)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (redir->type == APPEND_REDIR)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	return (fd);
}