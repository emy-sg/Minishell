#include "../../minishell.h"

//int	**pipe_fd(int pipe_length)
//{
//	int	**fd;
//	int	i;

//	i = 0;
//	fd = (int **)ft_fcalloc(sizeof(int *), pipe_length);
//	if (fd == NULL)
//		return (NULL);
//	while (i < pipe_length)
//	{
//		fd[i] = (int *)ft_fcalloc(sizeof(int), 2);
//		if (fd[i] == NULL || pipe(fd[i]) == -1)
//		{
//			free_double_int(fd);
//			return (NULL);
//		}
//		i++;
//	}
//	return (fd);
//}

//int	*pipe_fd(void)
//{
//	int	fd[2];

//	if (pipe(fd) == -1)
//		return (NULL);
//	return (fd);
//}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_ast	*the_cmd;
	int		fd[2];
	int		i;

	i = 0;
	the_cmd = s_ast;
	if (pipe(fd) == -1)
		return (sys_error(s_ast->argv[0], NULL));
	while (i < s_ast->nbr_pipes)
	//while (i < s_ast->nbr_pipes)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (sys_error(s_ast->argv[0], s_ast->argv[1]));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (sys_error(s_ast->argv[0], s_ast->argv[1]));
		printf("%d\n", the_cmd->nbr_pipes);
		//ft_cmd(the_cmd, env_export);
		print_export(env_export->export);

		the_cmd = the_cmd->child_cmd;
		i++;
	}
	return (EXIT_SUCCESS);
}