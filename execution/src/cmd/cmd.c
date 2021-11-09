/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:37:42 by emallah           #+#    #+#             */
/*   Updated: 2021/11/04 17:31:49 by isghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int ft_cmd_phase_1(t_ast *s_ast, t_env_export *env_export)
{
	int	executed;

	executed = 0;
	if (ft_strcstr(s_ast->argv[0], "cd"))
	{
		executed = 1;
		if (cd(s_ast, env_export) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	else if (ft_strcstr(s_ast->argv[0], "pwd"))
	{
		executed = 1;
		if (print_pwd() == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	return (executed);
}

int ft_cmd_phase_2(t_ast *s_ast, t_env_export *env_export)
{
	int	executed;

	executed = 0;
	if (ft_strcstr(s_ast->argv[0], "export"))
	{
		executed = 1;
		if (ft_export(s_ast, env_export) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	else if (ft_strcstr(s_ast->argv[0], "env"))
	{
		executed = 1;
		if (env(env_export->env) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	return (executed);
}

int ft_cmd_phase_3(t_ast *s_ast, t_env_export *env_export)
{
	int	executed;

	executed = 0;
	if (ft_strcstr(s_ast->argv[0], "unset"))
	{
		executed = 1;
		if (unset(s_ast, env_export) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	else if (ft_strcstr(s_ast->argv[0], "echo"))
	{
		executed = 1;
		if (ft_echo(s_ast) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	return (executed);
}

int ft_cmd_phase_4(t_ast *s_ast, t_env_export *env_export)
{
	int	executed;

	executed = 0;
	if (ft_strcstr(s_ast->argv[0], "exit"))
	{
		executed = 1;
		if (ft_exit(s_ast) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
	}
	else
	{
		executed = 1;
		if (other(s_ast, env_export) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], s_ast->argv[1]);	
	}
	return (executed);
}

int ft_cmd(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_cmd_phase_1(s_ast, env_export))
		return (EXIT_SUCCESS);
	else if (ft_cmd_phase_2(s_ast, env_export))
		return (EXIT_SUCCESS);
	else if (ft_cmd_phase_3(s_ast, env_export))
		return (EXIT_SUCCESS);
	else if (ft_cmd_phase_4(s_ast, env_export))
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	execute_command(t_ast *s_ast, t_env_export *env_export)
{
	t_cmd cmd;
	int stdout_fd;
	
	cmd.fdin = 0;
	cmd.fdout = 1;
	stdout_fd = dup(1);
	if (s_ast->redir)
		cmd.fdout = redirection(s_ast);
	if (cmd.fdout > 0)
	{
		if (dup2(cmd.fdout, STDOUT_FILENO) < 0)
			return (sys_error(s_ast->argv[0], s_ast->argv[1]));
		close(cmd.fdout);
	}
	ft_cmd(s_ast, env_export);
	if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		return (sys_error(s_ast->argv[0], s_ast->argv[1]));
	close(stdout_fd);
	return (EXIT_SUCCESS);
}
