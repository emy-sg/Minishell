/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:46:13 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:46:15 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	update_env_old_pwd(char **env, char *old_pwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strbstr(env[i], "OLDPWD="))
		{
			free(env[i]);
			env[i] = ft_fstrjoin("OLDPWD=", old_pwd);
			if (env[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	update_env_pwd(char **env, char *new_pwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strbstr(env[i], "PWD="))
		{
			free(env[i]);
			env[i] = ft_fstrjoin("PWD=", new_pwd);
			if (env[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	update_arg_env(char **env, char *var_name, char *var_value)
{
	int		i;
	char	*new_arg;
	
	i = 0;
	new_arg = ft_fstrjoin(var_name, "=");
	if (new_arg == NULL)
		return (EXIT_FAILURE);
	while (env[i])
	{
		if (ft_strbstr(env[i], new_arg))
		{
			free(env[i]);
			env[i] = ft_fstrjoin(new_arg, var_value);
			if (env[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
