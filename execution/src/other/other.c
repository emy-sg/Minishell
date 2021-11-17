/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:43:35 by emallah           #+#    #+#             */
/*   Updated: 2021/11/17 04:09:50 by isghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	other(t_ast *s_ast, t_env_export *env_export)
{
	int		status;
	pid_t	pid;

	pid = fork();
	global.global = 1;
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
		run_cmd(s_ast, env_export);
	waitpid(pid, &status, 0);
	global.signaled = 0;
	if (WIFSIGNALED(status))
	{
		global.signaled = 1;
		global.signal = WTERMSIG(status);
		if (global.signaled && global.signal == SIGQUIT)
		{
			printf("Quit:3\n");
			global.status = 131;
		}
	}
	global.global = 0;
	if (WEXITSTATUS(status) != 0)
		global.status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

void	run_cmd(t_ast *s_ast, t_env_export *env_export)
{
	if (str_includes(s_ast->argv[0], '/') == EXIT_SUCCESS)
		rum_cmd_abs_path(s_ast, env_export);
	else
		rum_cmd_env_path(s_ast, env_export);
}
