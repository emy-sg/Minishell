/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:23:28 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 14:23:29 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	add_env_export(t_env_export *env_export, char **temp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (export_exist(env_export->export, temp[0]) == EXIT_SUCCESS)
		ret = update_arg_export(env_export->export, temp[0], temp[1]);
	else if (ret == EXIT_SUCCESS)
		ret = add_arg_export(env_export, temp[0], temp[1]);
	if (ret == EXIT_SUCCESS && env_exist(env_export->env, temp[0]) == EXIT_SUCCESS)
		ret = update_arg_env(env_export->env, temp[0], temp[1]);
	else if (ret == EXIT_SUCCESS)
		ret = add_arg_env(env_export, temp[0], temp[1]);
	free_double(temp);
	return (ret);
}

int	push_arg_export(t_env_export *env_export, char *arg)
{
	int		i;
	char	**temp;

	i = 0;
	temp = (char **)ft_fcalloc(sizeof(char *),
			ft_fstrlen_double((const char **)env_export->export) + 2);
	if (temp == NULL)
		return (EXIT_FAILURE);
	while (env_export->export[i])
	{
		temp[i] = ft_fstrdup(env_export->export[i]);
		if (temp[i] == NULL)
		{
			free_double(temp);
			return (EXIT_FAILURE);
		}
		i++;
	}
	temp[i] = ft_strjoin("declare -x ", arg);
	temp[i + 1] = NULL;
	free_double(env_export->export);
	env_export->export = temp;
	return (EXIT_SUCCESS);
}

int	add_export(t_env_export *env_export, char *arg)
{
	char	*temp;
	char	*variable_name;

	temp = ft_strjoin("declare -x ", arg);
	if (temp == NULL)
		return (EXIT_FAILURE);
	variable_name = ft_strjoin(temp, "=");
	free(temp);
	if (variable_name == NULL)
		return (EXIT_FAILURE);
	if (export_exist(env_export->export, variable_name) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (push_arg_export(env_export, arg));
	return (EXIT_SUCCESS);
}
