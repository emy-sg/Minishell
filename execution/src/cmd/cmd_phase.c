/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_phase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <emallah@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:34:35 by emallah           #+#    #+#             */
/*   Updated: 2021/11/15 15:34:37 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_cmd_phase_1(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "cd"))
	{
		g_status = 0;
		if (cd(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "pwd"))
	{
		g_status = 0;
		if (print_pwd() == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_cmd_phase_2(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "export"))
	{
		g_status = 0;
		if (ft_export(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "env"))
	{
		g_status = 0;
		if (env(env_export->env) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_cmd_phase_3(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "unset"))
	{
		g_status = 0;
		if (unset(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "echo"))
	{
		g_status = 0;
		if (ft_echo(s_ast) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_cmd_phase_4(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "exit"))
	{
		if (ft_exit(s_ast) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else
	{
		if (other(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
