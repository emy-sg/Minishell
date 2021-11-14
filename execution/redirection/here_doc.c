#include "../../minishell.h"

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
	//int 	fdout;
	
	limiter_w_efl = ft_fstrjoin(limiter, "\n");
	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
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
	return (open("/tmp/heredoc", O_RDONLY, 0777));
}