/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:45:10 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:45:12 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	add_arg_env(t_env_export *env_export, char *var_name, char *var_value)
{
	int		i;
	char	**temp;
	char	*var_name_w_equal;

	i = 0;
	temp = (char **)ft_fcalloc(sizeof(char *),
			ft_fstrlen_double((const char **)env_export->env) + 2);
	if (temp == NULL)
		return (EXIT_FAILURE);
	while (env_export->env[i])
	{
		temp[i] = ft_fstrdup(env_export->env[i]);
		if (temp[i] == NULL)
		{
			free_double(temp);
			return (EXIT_FAILURE);
		}
		i++;
	}
	var_name_w_equal = ft_fstrjoin(var_name, "=");
	if (var_name_w_equal == NULL)
	{
		free_double(temp);
		return (EXIT_FAILURE);
	}
	temp[i] = ft_fstrjoin(var_name_w_equal, var_value);
	free(var_name_w_equal);
	if (temp[i] == NULL)
	{
		free_double(temp);
		return (EXIT_FAILURE);
	}
	free_double(env_export->env);
	env_export->env = temp;
	return (EXIT_SUCCESS);
}
