#include "../../minishell.h"

int	ft_cmd_pipe(t_ast *the_cmd, t_env_export *env_export)
{
	if (the_cmd->redir)
		return (ft_redir(the_cmd, env_export, 0));
	return (ft_cmd(the_cmd, env_export));
}

int	cmd_has_here_doc(t_ast *the_cmd)
{
	int i;

	i = 0;
	if (the_cmd->redir == NULL)
		return (EXIT_FAILURE);
	while (the_cmd->redir[i] != NULL)
	{
		if (the_cmd->redir[i]->type == HERE_DOC_REDIR)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	nbr_here_doc(t_ast *s_ast)
{
	t_ast	*the_cmd;
	int		length;
	int		i;

	i = 0;
	length = 0;
	the_cmd = s_ast;
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
			length++;
		i++;
	}
	return (length);
}

int	**here_doc_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_ast	*the_cmd;
	int		**here_doc_fd;
	int		here_doc_length;
	int		i;
	int		j;

	i = 0;
	j = 0;
	here_doc_length = nbr_here_doc(s_ast);
	if (here_doc_length == 0)
		return (NULL);
	here_doc_fd = (int **)ft_fcalloc(sizeof(int *), here_doc_length);
	the_cmd = s_ast;
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (cmd_has_here_doc(the_cmd) == EXIT_SUCCESS)
		{
			here_doc_fd[j] = (int *)ft_fcalloc(sizeof(int), 2);
			pipe(here_doc_fd[j]);
			ft_redir(the_cmd, env_export, here_doc_fd[j][1]);
			j++;
		}
		i++;
	}
	return (here_doc_fd);
}

t_cmd_pipe	*init_cmd_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_cmd_pipe	*cmd_pipe;

	cmd_pipe = (t_cmd_pipe *)ft_fcalloc(sizeof(t_cmd_pipe), 2);
	if (cmd_pipe == NULL)
		return (NULL);
	cmd_pipe->child_ps_id = (pid_t *)ft_fcalloc(sizeof(pid_t), s_ast->nbr_pipes + 1);
	if (cmd_pipe->child_ps_id == NULL)
		return (NULL);
	cmd_pipe->here_doc_length = nbr_here_doc(s_ast);
	cmd_pipe->here_doc_fd = here_doc_pipe(s_ast, env_export);
	cmd_pipe->cmd = s_ast;
	cmd_pipe->fdin = 0;
	return (cmd_pipe);
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_cmd_pipe	*cmd_pipe;
	int			i;
	int			j;

	i = 0;
	j = 0;
	cmd_pipe = init_cmd_pipe(s_ast, env_export);
	if (cmd_pipe == NULL)
		return (ERROR);
	while (i <= s_ast->nbr_pipes)
	{
		// cmd
		cmd_pipe->cmd = cmd_pipe->cmd->child_cmd;
		//her doc
		if (cmd_has_here_doc(cmd_pipe->cmd) == EXIT_SUCCESS)
		{
			cmd_pipe->fdin = cmd_pipe->here_doc_fd[j++][0];
			i++;
			continue;
		}
		//pipe
		if (i < s_ast->nbr_pipes && pipe(cmd_pipe->pipe_fd) == -1)
			return (sys_error(NULL, NULL));
		//fork
		cmd_pipe->pid = fork();
		if (cmd_pipe->pid != 0)
			cmd_pipe->child_ps_id[i] = cmd_pipe->pid;
		if (cmd_pipe->pid == 0)
		{
			//close all fds
			int a = 0;
			while (a < cmd_pipe->here_doc_length)
			{
				close(cmd_pipe->here_doc_fd[a][0]);
				close(cmd_pipe->here_doc_fd[a][1]);
				a++;
			}
			//[END] close all fds
			if (i == 0)
			{
				dup2(0, STDIN_FILENO);
				dup2(cmd_pipe->pipe_fd[1], STDOUT_FILENO);
			}
			else if (i == s_ast->nbr_pipes)
			{
				dup2(cmd_pipe->fdin, STDIN_FILENO);
				dup2(1, STDOUT_FILENO);
			}
			else
			{
				dup2(cmd_pipe->fdin, STDIN_FILENO);
				dup2(cmd_pipe->pipe_fd[1], STDOUT_FILENO);
			}
			close(cmd_pipe->pipe_fd[0]);
			ft_cmd_pipe(cmd_pipe->cmd, env_export);
			close(cmd_pipe->pipe_fd[1]);
			close(cmd_pipe->fdin);
			exit(g_status);
		}
		close(cmd_pipe->fdin);
		cmd_pipe->fdin = cmd_pipe->pipe_fd[0];
		close(cmd_pipe->pipe_fd[1]);
		i++;
	}
	close(cmd_pipe->pipe_fd[0]);
	int a = 0;
	while (a < cmd_pipe->here_doc_length)
	{
		close(cmd_pipe->here_doc_fd[a][0]);
		close(cmd_pipe->here_doc_fd[a][1]);
		a++;
	}
	int status;
	i = 0;
	while (i <= s_ast->nbr_pipes)
	{
		if (cmd_pipe->child_ps_id[i] != 0)
			waitpid(cmd_pipe->child_ps_id[i], &status, 0);
		i++;
	}
	if (WEXITSTATUS(status) != 0)
		g_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);

	//i = 0;
	//pidd = (int *)ft_calloc(sizeof(int), s_ast->nbr_pipes + 1);
	//the_cmd = s_ast;
	//while(i <= s_ast->nbr_pipes)
	//{
	//	the_cmd = the_cmd->child_cmd;
	//	if (i < s_ast->nbr_pipes && pipe(pipe_fd) == -1)
	//		return (sys_error(NULL, NULL));
	//	pid = fork();
	//	if (pid != 0)
	//		pidd[i] = pid;
	//	if (pid == 0)
	//	{
	//		if (i == 0)
	//		{
	//			dup2(0, STDIN_FILENO);
	//			dup2(pipe_fd[1], STDOUT_FILENO);
	//		}
	//		else if (i == s_ast->nbr_pipes)
	//		{
	//			dup2(in_fd, STDIN_FILENO);
	//			dup2(1, STDOUT_FILENO);
	//		}
	//		else
	//		{
	//			dup2(in_fd, STDIN_FILENO);
	//			dup2(pipe_fd[1], STDOUT_FILENO);
	//		}
	//		close(pipe_fd[0]);
	//		ft_cmd_pipe(the_cmd, env_export);
	//		close(pipe_fd[1]);
	//		close(in_fd);
	//		exit(g_status);
	//	}
	//	close(in_fd);
	//	in_fd = pipe_fd[0];
	//	close(pipe_fd[1]);
	//	i++;
	//}
	//close(pipe_fd[0]);
	//int status;
	//i = 0;
	//while (i <= s_ast->nbr_pipes)
	//{
	//	waitpid(pidd[i], &status, 0);
	//	i++;
	//}
	//if (WEXITSTATUS(status) != 0)
	//	g_status = WEXITSTATUS(status);
	//return (EXIT_SUCCESS);
}