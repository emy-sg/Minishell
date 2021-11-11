#include "../../minishell.h"

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
		if (s_ast->redir[i]->type == INPUT_REDIR || s_ast->redir[i]->type == HERE_DOC_REDIR)
			redirect->fdin = redir_fdin(s_ast->redir[i]);
		if (s_ast->redir[i]->type == OVERWRITE_REDIR || s_ast->redir[i]->type == APPEND_REDIR)
			redirect->fdout = redir_fdout(s_ast->redir[i]);
		if (redirect->fdin == -1 || redirect->fdout == -1)
		{
			g_status = 1;
			sys_error(NULL, s_ast->redir[i]->file_name);
			return (NULL);
		}
		i++;
	}
	return (redirect);
}

char *mini_gnl(void)
{
	char *buf;
	char *temp;
	char *line;
	
	line = (char *)ft_calloc(sizeof(char), 2);
	buf = (char *)ft_calloc(sizeof(char), 2);
	while (read(STDIN_FILENO, buf, 1))
	{
		temp = ft_fstrjoin(line, buf);
		free(line);
		line = ft_fstrdup(temp);
		free(temp);
		if (buf[0] == '\n')
			break;
	}
	free(buf);
	return (line);
}

int here_doc(char *limiter)
{
	int		fd;
	char	*line;
	char	*limiter_w_efl;
	
	limiter_w_efl = ft_fstrjoin(limiter, "\n");
	fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = mini_gnl();
		if (ft_strcstr(limiter_w_efl, line))
		{
			free(limiter_w_efl);
			free(line);
			break ;
		}
		write(fd, line, ft_fstrlen(line));
		free(line);
	}
	close(fd);
	return (open("temp", O_RDONLY, 0777));
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

int	simple_redir_in(t_redirect *redirect, t_ast *s_ast)
{
	if (ft_strcstr(s_ast->argv[0], "exit") == NULL)
	{
		if (dup2(redirect->fdin, STDIN_FILENO) < 0)
			return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	}
	return (EXIT_SUCCESS);
}

int	simple_redir_out(t_redirect *redirect, t_ast *s_ast)
{
	if (ft_strcstr(s_ast->argv[0], "exit") == NULL)
	{
		if (dup2(redirect->fdout, STDOUT_FILENO) < 0)
			return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	}
	return (EXIT_SUCCESS);
}

int	redir_in_back_to_normal(t_redirect *redirect, t_ast *s_ast)
{
	close(redirect->fdin); 
	if (dup2(redirect->stdin_fd, STDIN_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->stdin_fd);
	return (EXIT_SUCCESS);
}

int	redir_out_back_to_normal(t_redirect *redirect, t_ast *s_ast)
{
	close(redirect->fdout); 
	if (dup2(redirect->stdout_fd, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(redirect->stdout_fd);
	return (EXIT_SUCCESS);
}


int	ft_redir(t_ast *s_ast, t_env_export *env_export)
{
	t_redirect *redirect;
	
	redirect = init_redirect(s_ast);
	if (redirect == NULL)
		return (EXIT_SUCCESS);
	if (redirect->fdin != 0)
		simple_redir_in(redirect, s_ast);
	if (redirect->fdout != 0)
		simple_redir_out(redirect, s_ast);
	ft_cmd(s_ast, env_export);
	if (redirect->fdin != 0)
		redir_in_back_to_normal(redirect, s_ast);
	if (redirect->fdout != 0)
		redir_out_back_to_normal(redirect, s_ast);
	free(redirect);
	return (EXIT_SUCCESS);
}
