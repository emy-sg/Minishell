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
	redirect->stdout_fd = dup(1);
	redirect->stdin_fd = dup(0);
	redirect->fdin = 0;
	redirect->fdout = 0;
	while (s_ast->redir[i])
	{
		redirect->fdin = redir_fdin(s_ast->redir[i]);
		redirect->fdout = redir_fdout(s_ast->redir[i]);
		if (redirect->fdin == -1 || redirect->fdout == -1)
		{
			sys_error(s_ast->argv[0], s_ast->redir[i]->file_name);
			return (NULL);
		}
		i++;
	}
	return (redirect);
}

int	simple_redir_in(t_redirect *redirect, t_ast *s_ast, t_env_export *env_export)
{
	if (dup2(redirect->fdin, STDIN_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	ft_cmd(s_ast, env_export);
	close(redirect->fdin); 
	if (dup2(redirect->stdin_fd, STDIN_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->stdin_fd);
	return (EXIT_SUCCESS);
}

int	simple_redir_out(t_redirect *redirect, t_ast *s_ast, t_env_export *env_export)
{
	if (dup2(redirect->fdout, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	ft_cmd(s_ast, env_export);
	close(redirect->fdout); 
	if (dup2(redirect->stdout_fd, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->stdout_fd);
	return (EXIT_SUCCESS);
}

int	simple_redir(t_ast *s_ast, t_env_export *env_export)
{
	t_redirect *redirect;

	redirect = init_redirect(s_ast);
	if (redirect == NULL)
		return (EXIT_SUCCESS);
	if (redirect->fdin != 0)
		return (simple_redir_in(redirect, s_ast, env_export));
	return (simple_redir_out(redirect, s_ast, env_export));
}
