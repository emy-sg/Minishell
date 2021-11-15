#include "../../minishell.h"

int exec_here_doc(t_ast *s_ast, char *heredoc_file_name)
{
	int i;

	i = 0;
	while (s_ast->redir[i] != NULL)
	{
		if (s_ast->redir[i]->type == HERE_DOC_REDIR)
		{
			if (here_doc(s_ast->redir[i]->file_name, heredoc_file_name) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	cmd_has_here_doc(t_ast *s_ast)
{
	int i;

	i = 0;
	if (s_ast->redir == NULL)
		return (EXIT_FAILURE);
	while (s_ast->redir[i] != NULL)
	{
		if (s_ast->redir[i]->type == HERE_DOC_REDIR)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	nbr_here_doc(t_ast *s_ast)
{
	int		length;
	int		i;

	i = 0;
	length = 0;
	while (s_ast->redir[i])
	{
		if (s_ast->redir[i]->type == HERE_DOC_REDIR)
			length++;
		i++;
	}
	if (length == 0)
		return (-1);
	return (length);
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

int here_doc(char *limiter, char *heredoc_file_name)
{
	int		fd;
	char	*line;
	char	*limiter_w_efl;
	
	limiter_w_efl = ft_fstrjoin(limiter, "\n");
	fd = open(heredoc_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (sys_error(NULL, NULL));
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
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
	return (EXIT_SUCCESS);
}