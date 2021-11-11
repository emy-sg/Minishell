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
		g_status = 0;
		if (cd(s_ast, env_export) == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
	}
	else if (ft_strcstr(s_ast->argv[0], "pwd"))
	{
		executed = 1;
		g_status = 0;
		if (print_pwd() == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
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
		g_status = 0;
		if (ft_export(s_ast, env_export) == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
	}
	else if (ft_strcstr(s_ast->argv[0], "env"))
	{
		executed = 1;
		g_status = 0;
		if (env(env_export->env) == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
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
		g_status = 0;
		if (unset(s_ast, env_export) == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
	}
	else if (ft_strcstr(s_ast->argv[0], "echo"))
	{
		executed = 1;
		g_status = 0;
		if (ft_echo(s_ast) == EXIT_FAILURE)
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
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
		{
			g_status = 1;
			sys_error(s_ast->argv[0], NULL);
		}
	}
	else
	{
		executed = 1;
		g_status = 0;
		if (other(s_ast, env_export) == EXIT_FAILURE)
			sys_error(s_ast->argv[0], NULL);
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
	if (s_ast->nbr_pipes > 0)
		return (ft_pipe(s_ast, env_export));
	if (s_ast->redir)
		return (ft_redir(s_ast, env_export));
	return (ft_cmd(s_ast, env_export));
}
