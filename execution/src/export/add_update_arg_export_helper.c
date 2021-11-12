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

int	export_exist(char **export, char *var_name)
{
	char *temp;
	char *var_name_w_equal;

	temp = ft_fstrjoin("declare -x ", var_name);
	if (temp == NULL)
		return (ERROR);
	var_name_w_equal = ft_fstrjoin(temp, "=");
	free(temp);
	if (var_name_w_equal == NULL)
		return (ERROR);
	if (export_exist_try_1(export, var_name_w_equal) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	var_name_w_equal[ft_fstrlen(var_name_w_equal) - 1] = '\0';
	return (export_exist_try_2(export, var_name_w_equal));
}

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
