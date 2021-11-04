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
	if (ft_strbstr(s_ast->argv[0], "cd"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (cd(&cmds[i]) == EXIT_FAILURE)
			// return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "pwd"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (print_pwd() == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "export"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (ft_export(&cmds[i]) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "env"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (env(cmds[i].env_export->env) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "unset"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (unset(&cmds[i]) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "echo"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (echo(&cmds[i]) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else if (ft_strbstr(s_ast->argv[0], "exit"))
	{
		printf("%s\n", s_ast->argv[0]);
		// if (ft_exit(&cmds[i]) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));
	}
	else
	{
		printf("%s\n", s_ast->argv[0]);
		// if (other(&cmds[i]) == EXIT_FAILURE)
		// 	return (sys_error(cmds[i].cmd, cmds[i].arg[0]));	
	}
	return (EXIT_SUCCESS);
}
