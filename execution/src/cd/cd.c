/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:32:08 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:32:09 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	cd(t_ast *s_ast, t_env_export *env_export)
{
	int		ret;
	char	*path;

	path = cd_path(s_ast->argv[1], env_export->env);
	if (path == NULL)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		free(path);
		return (EXIT_FAILURE);
	}
	ret = update_env_export(env_export);
	free(path);
	return (ret);
}
