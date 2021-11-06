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

int	execute_command(t_ast *s_ast, t_env_export *env_export)
{
	if (!s_ast)
		env(env_export->env);
	if (ft_strcstr(s_ast->argv[0], "cd"))
	{
		 if (cd(s_ast, env_export) == EXIT_FAILURE)
			 return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "pwd"))
	{
		 if (print_pwd() == EXIT_FAILURE)
		 	return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "export"))
	{
		if (ft_export(s_ast, env_export) == EXIT_FAILURE)
			return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "env"))
	{
		if (env(env_export->env) == EXIT_FAILURE)
			return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "unset"))
	{
		if (unset(s_ast, env_export) == EXIT_FAILURE)
			return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "echo"))
	{
		if (ft_echo(s_ast) == EXIT_FAILURE)
			return (sys_error(s_ast->argv[0], NULL));
	}
	else if (ft_strcstr(s_ast->argv[0], "exit"))
	{
		if (ft_exit(s_ast) == EXIT_FAILURE)
			return (sys_error(s_ast->argv[0], NULL));
	}
	else
	{
		 if (other(s_ast, env_export) == EXIT_FAILURE)
		 	return (sys_error(s_ast->argv[0], s_ast->argv[1]));	
	}
	return (EXIT_SUCCESS);
}
