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
	if (s_ast->nbr_pipes > 0)
		return (ft_pipe(s_ast, env_export));
	if (s_ast->redir)
		return (ft_redir(s_ast, env_export));
	return (ft_cmd(s_ast, env_export));
}

int ft_cmd(t_ast *s_ast, t_env_export *env_export)
{
	int ret;

	g_status = 0;
	ret = ft_cmd_phase_1(s_ast, env_export);
	if (ret == EXIT_FAILURE)
		ret = ft_cmd_phase_2(s_ast, env_export);
	if (ret == EXIT_FAILURE)
		ret = ft_cmd_phase_3(s_ast, env_export);
	if (ret == EXIT_FAILURE)
		ret = ft_cmd_phase_4(s_ast, env_export);
	return (ret);
}
