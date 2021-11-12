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

int	add_arg_export(t_env_export *env_export, char *var_name, char *var_value)
{
	int		i;
	char	**temp;


	i = 0;
	temp = refill_export(env_export->export);
	if (temp == NULL)
		return (ERROR);
	temp[i] = added_arg(var_name, var_value);
	if (temp[i] == NULL)
	{
		free_double(temp);
		return (ERROR);
	}
	free_double(env_export->export);
	env_export->export = temp;
	return (EXIT_SUCCESS);
}

char	*added_arg(char *var_name, char *var_value)
{
	char	*helper;
	char	*var_name_w_equal;
	char	*temp;


	helper = ft_fstrjoin("declare -x ", var_name);
	if (helper == NULL)
		return (NULL);
	var_name_w_equal = ft_fstrjoin(helper, "=");
	free(helper);
	if (var_name_w_equal == NULL)
		return (NULL);
	temp = ft_fstrjoin_w_quote(var_name_w_equal, var_value);
	free(var_name_w_equal);
	return (temp);
}

char	**refill_export(char **export)
{
	int		i;
	char	**temp;

	i = 0;
	temp = (char **)ft_fcalloc(sizeof(char *),
			ft_fstrlen_double((const char **)export) + 2);
	if (temp == NULL)
		return (NULL);
	while (export[i])
	{
		temp[i] = ft_fstrdup(export[i]);
		if (temp[i] == NULL)
		{
			free_double(temp);
			return (NULL);
		}
		i++;
	}
	return (temp);
}

int	update_arg_export(char **export, char *var_name, char *var_value)
{
	int		i;
	char	*temp;
	char	*new_arg;
	
	i = 0;
	temp = ft_fstrjoin("declare -x ", var_name);
	if (temp == NULL)
		return (ERROR);
	while (export[i])
	{
		if (ft_strbstr(export[i], temp))
		{
			new_arg = ft_fstrjoin(temp, "=");
			free(export[i]);
			free(temp);
			if (new_arg == NULL)
				return (ERROR);
			export[i] = ft_fstrjoin_w_quote(new_arg, var_value);
			if (export[i] == NULL)
				return (ERROR);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}