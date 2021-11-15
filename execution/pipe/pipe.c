#include "../../minishell.h"

int	ft_cmd_pipe(t_ast *s_ast, t_env_export *env_export, char *heredoc_file_name)
{
	if (s_ast->redir)
		return (ft_redir(s_ast, env_export, heredoc_file_name));
	return (ft_cmd(s_ast, env_export));
}

int nbr_here_doc_all_cmd(t_ast *s_ast)
{
	t_ast   *the_cmd;
	int     i;
	int     length;

	the_cmd = s_ast;
	i = 0;
	length = 0;
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
			length++;
		i++;
	}
	if (length == 0)
		return (-1);
	return (length);
}

char    *here_doc_file_name_gen(int j)
{
	char *nbr;
	char *file_name;
	
	nbr = ft_itoa(j);
	file_name = ft_fstrjoin("/tmp/heredoc-", nbr);
	free (nbr);
	return (file_name);
}

char **heredoc_files_names_all_cmd(t_ast *s_ast)
{
	t_ast   *the_cmd;
	char    **heredoc_files_names;
	int     i;
	int     j;
	int     length;

	i = 0;
	j = 0;
	length = nbr_here_doc_all_cmd(s_ast);
	if (length == -1)
		return (NULL);
	heredoc_files_names = (char **)ft_fcalloc(sizeof(char *), length + 1);
	if (heredoc_files_names == NULL)
		return (NULL);
	the_cmd = s_ast;
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
		{
			heredoc_files_names[j] = here_doc_file_name_gen(j);
			j++;
		}
		i++;
	}
	return (heredoc_files_names);
}

int exec_here_doc_all_cmd(t_ast *s_ast, char **heredoc_files_names)
{
	t_ast   *the_cmd;
	int     i;
	int     j;
	
	i = 0;
	j = 0;
	the_cmd = s_ast;
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
		{
			if (exec_here_doc(the_cmd, heredoc_files_names[j++]) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	char **heredoc_files_names;
	int i;
	int j;
	t_ast   *the_cmd;
	int *pidd;
	pid_t pid;
	int pipe_fd[2];
	int in_fd = -1;
	
	
	heredoc_files_names = heredoc_files_names_all_cmd(s_ast);
	if (heredoc_files_names != NULL)
		exec_here_doc_all_cmd(s_ast, heredoc_files_names);
	i = 0;
	j = -1;
	pidd = (int *)ft_calloc(sizeof(int), s_ast->nbr_pipes + 1);
	the_cmd = s_ast;
	while(i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (i < s_ast->nbr_pipes && pipe(pipe_fd) == -1)
			return (sys_error(NULL, NULL));
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
			j++;
		pid = fork();
		if (pid != 0)
			pidd[i] = pid;
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(0, STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
			}
			else if (i == s_ast->nbr_pipes)
			{
				dup2(in_fd, STDIN_FILENO);
				dup2(1, STDOUT_FILENO);
			}
			else
			{
				dup2(in_fd, STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
			}
			close(pipe_fd[0]);
			if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
				ft_cmd_pipe(the_cmd, env_export, heredoc_files_names[j]);
			else
				ft_cmd_pipe(the_cmd, env_export, NULL);
			close(pipe_fd[1]);
			close(in_fd);
			exit(g_status);
		}
		close(in_fd);
		in_fd = pipe_fd[0];
		close(pipe_fd[1]);
		i++;
	}
	close(pipe_fd[0]);
	int status;
	i = 0;
	while (i <= s_ast->nbr_pipes)
	{
		if (pidd[i] != 0) 
			waitpid(pidd[i], &status, 0);
		i++;
	}
	if (WEXITSTATUS(status) != 0)
		g_status = WEXITSTATUS(status);
	free(pidd);
	if (heredoc_files_names != NULL)
		free_double(heredoc_files_names);
	return (EXIT_SUCCESS);
	
	// ========================================================
	// t_cmd_pipe	*cmd_pipe;
	// int			i;
	// int			j;

	// i = 0;
	// j = 0;
	// cmd_pipe = init_cmd_pipe(s_ast, env_export);
	// if (cmd_pipe == NULL)
	// 	return (ERROR);
	// while (i <= s_ast->nbr_pipes)
	// {
	// 	// cmd
	// 	cmd_pipe->cmd = cmd_pipe->cmd->child_cmd;
	// 	//her doc
	// 	if (cmd_has_here_doc(cmd_pipe->cmd) == EXIT_SUCCESS)
	// 	{
	// 		cmd_pipe->fdin = cmd_pipe->here_doc_fd[j++][0];
	// 		i++;
	// 		continue;
	// 	}
	// 	//pipe
	// 	if (i < s_ast->nbr_pipes && pipe(cmd_pipe->pipe_fd) == -1)
	// 		return (sys_error(NULL, NULL));
	// 	//fork
	// 	cmd_pipe->pid = fork();
	// 	if (cmd_pipe->pid != 0)
	// 		cmd_pipe->child_ps_id[i] = cmd_pipe->pid;
	// 	if (cmd_pipe->pid == 0)
	// 	{
	// 		//close all fds
	// 		int a = 0;
	// 		while (a < cmd_pipe->here_doc_length)
	// 		{
	// 			close(cmd_pipe->here_doc_fd[a][0]);
	// 			close(cmd_pipe->here_doc_fd[a][1]);
	// 			a++;
	// 		}
	// 		//[END] close all fds
	// 		if (i == 0)
	// 		{
	// 			dup2(0, STDIN_FILENO);
	// 			dup2(cmd_pipe->pipe_fd[1], STDOUT_FILENO);
	// 		}
	// 		else if (i == s_ast->nbr_pipes)
	// 		{
	// 			dup2(cmd_pipe->fdin, STDIN_FILENO);
	// 			dup2(1, STDOUT_FILENO);
	// 		}
	// 		else
	// 		{
	// 			dup2(cmd_pipe->fdin, STDIN_FILENO);
	// 			dup2(cmd_pipe->pipe_fd[1], STDOUT_FILENO);
	// 		}
	// 		close(cmd_pipe->pipe_fd[0]);
	// 		ft_cmd_pipe(cmd_pipe->cmd, env_export);
	// 		close(cmd_pipe->pipe_fd[1]);
	// 		close(cmd_pipe->fdin);
	// 		exit(g_status);
	// 	}
	// 	close(cmd_pipe->fdin);
	// 	cmd_pipe->fdin = cmd_pipe->pipe_fd[0];
	// 	close(cmd_pipe->pipe_fd[1]);
	// 	i++;
	// }
	// close(cmd_pipe->pipe_fd[0]);
	// int a = 0;
	// while (a < cmd_pipe->here_doc_length)
	// {
	// 	close(cmd_pipe->here_doc_fd[a][0]);
	// 	close(cmd_pipe->here_doc_fd[a][1]);
	// 	a++;
	// }
	// int status;
	// i = 0;
	// while (i <= s_ast->nbr_pipes)
	// {
	// 	if (cmd_pipe->child_ps_id[i] != 0)
	// 		waitpid(cmd_pipe->child_ps_id[i], &status, 0);
	// 	i++;
	// }
	// if (WEXITSTATUS(status) != 0)
	// 	g_status = WEXITSTATUS(status);
	// if (cmd_pipe->here_doc_fd)
	// 	free_double_int(cmd_pipe->here_doc_fd);
	// free(cmd_pipe->child_ps_id);
	// free(cmd_pipe);
	// return (EXIT_SUCCESS);
	// ========================================================
}