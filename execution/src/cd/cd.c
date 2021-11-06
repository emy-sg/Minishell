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
	char	*path;

	if (update_env_export_old_pwd(env_export) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	path = cd_path(s_ast->argv[1], env_export->env);
	if (path == NULL)
		return (EXIT_SUCCESS);
	if (chdir(path) != 0)
	{
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	if (update_env_export_pwd(env_export) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	update_env_export_old_pwd(t_env_export *env_export)
{
	char	*old_pwd;

	old_pwd = pwd();
	if (old_pwd == NULL)
		return (EXIT_FAILURE);
	if (update_env_old_pwd(env_export->env, old_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (update_export_old_pwd(env_export->export, old_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	update_env_export_pwd(t_env_export *env_export)
{
	char	*new_pwd;

	new_pwd = pwd();
	if (new_pwd == NULL)
		return (EXIT_FAILURE);
	if (update_env_pwd(env_export->env, new_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (update_export_pwd(env_export->export, new_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}