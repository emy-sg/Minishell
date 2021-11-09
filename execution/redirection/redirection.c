#include "../../minishell.h"

int	redir_fdin(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == INPUT_REDIR)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (redir->type == HERE_DOC_REDIR)
		fd = open(redir->file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
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

t_redirect	*init_redirect(t_ast *s_ast)
{
	t_redirect	*redirect;
	int			i;

	i = 0;
	redirect = (t_redirect *)ft_calloc(sizeof(t_redirect), 2);
	if (redirect == NULL)
	{
		sys_error(s_ast->argv[0], NULL);
		return (NULL);
	}
	redirect[0].stdout_fd = dup(1);
	redirect[0].stdin_fd = dup(0);
	redirect[0].fdin = 0;
	redirect[0].fdout = 0;
	while (s_ast->redir[i])
	{
		redirect[0].fdin = redir_fdin(s_ast->redir[i]);
		redirect[0].fdout = redir_fdin(s_ast->redir[i]);
		if (redirect[0].fdin == -1 || redirect[0].fdout == -1)
		{
			sys_error(s_ast->argv[0], s_ast->redir[i]->file_name);
			return (NULL);
		}
		i++;
	}
	return (redirect);
}

int	simple_redir(t_ast *s_ast, t_env_export *env_export)
{
	t_redirect *redirect;

	redirect = init_redirect(s_ast);
	if (redirect == NULL)
		return (EXIT_SUCCESS);
	if (dup2(redirect->fdout, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->fdout);
	ft_cmd(s_ast, env_export);
	if (dup2(redirect->stdout_fd, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->stdout_fd);
	return (EXIT_SUCCESS);
}
