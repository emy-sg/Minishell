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

int	export_exist_try_1(char **export, char *var_name_w_equal)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (ft_strbstr(export[i], var_name_w_equal))
		{
			free(var_name_w_equal);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	export_exist_try_2(char **export, char *var_name_w_equal)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (ft_strcstr(export[i], var_name_w_equal))
		{
			free (var_name_w_equal);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(var_name_w_equal);
	return (EXIT_FAILURE);
}

int	export_exist(char **export, char *var_name)
{
	char *temp;
	char *var_name_w_equal;

	temp = ft_strjoin("declare -x ", var_name);
	if (temp == NULL)
		return (EXIT_FAILURE);
	var_name_w_equal = ft_strjoin(temp, "=");
	free(temp);
	if (var_name_w_equal == NULL)
		return (EXIT_FAILURE);
	if (export_exist_try_1(export, var_name_w_equal) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	var_name_w_equal[ft_fstrlen(var_name_w_equal) - 1] = '\0';
	return (export_exist_try_2(export, var_name_w_equal));
}

int	update_arg_export(char **export, char *var_name, char *var_value)
{
	int		i;
	char	*temp;
	char	*new_arg;
	
	i = 0;
	temp = ft_strjoin("declare -x ", var_name);
	if (temp == NULL)
		return (EXIT_FAILURE);
	new_arg = ft_strjoin(temp, "=");
	free(temp);
	if (new_arg == NULL)
		return (EXIT_FAILURE);
	while (export[i])
	{
		if (ft_strbstr(export[i], new_arg))
		{
			free(export[i]);
			export[i] = ft_strjoin_w_quote(new_arg, var_value);
			if (export[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	add_arg_export(t_env_export *env_export, char *var_name, char *var_value)
{
	int		i;
	char	**temp;
	char	*helper;
	char	*var_name_w_equal;

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
	helper = ft_strjoin("declare -x ", var_name);
	if (helper == NULL)
	{
		free_double(temp);
		return (EXIT_FAILURE);
	}
	var_name_w_equal = ft_strjoin(helper, "=");
	free(helper);
	if (var_name_w_equal == NULL)
	{
		free_double(temp);
		return (EXIT_FAILURE);
	}
	temp[i] = ft_strjoin_w_quote(var_name_w_equal, var_value);
	free(var_name_w_equal);
	if (temp[i] == NULL)
	{
		free_double(temp);
		return (EXIT_FAILURE);
	}
	free_double(env_export->export);
	env_export->export = temp;
	return (EXIT_SUCCESS);
}
