/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:46:49 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:46:50 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	env_exist_try_1(char **env, char *var_name_w_equal)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strbstr(env[i], var_name_w_equal))
		{
			free(var_name_w_equal);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(var_name_w_equal);
	return (EXIT_FAILURE);
}

int	env_exist(char **env, char *var_name)
{
	char *var_name_w_equal;

	var_name_w_equal = ft_strjoin(var_name, "=");
	if (var_name_w_equal == NULL)
		return (EXIT_FAILURE);
	if (env_exist_try_1(env, var_name_w_equal) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

char	**init_env(const char **menv)
{
	int		i;
	char	**env;

	i = 0;
	env = (char **)ft_fcalloc(sizeof(char *), ft_fstrlen_double(menv) + 1);
	if (env == NULL)
		return (NULL);
	while (menv[i])
	{
		env[i] = ft_fstrdup(menv[i]);
		if (env[i] == NULL)
		{
			free_double(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
