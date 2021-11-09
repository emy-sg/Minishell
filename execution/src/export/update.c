/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:22:40 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 14:22:45 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	update_export_old_pwd(char **export, char *old_pwd)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (ft_strbstr(export[i], "declare -x OLDPWD="))
		{
			free(export[i]);
			export[i] = ft_fstrjoin("declare -x OLDPWD=", old_pwd);
			free(old_pwd);
			if (export[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(old_pwd);
	return (EXIT_SUCCESS);
}

int	update_export_pwd(char **export, char *new_pwd)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (ft_strbstr(export[i], "declare -x PWD="))
		{
			free(export[i]);
			export[i] = ft_fstrjoin("declare -x PWD=", new_pwd);
			free(new_pwd);
			if (export[i] == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(new_pwd);
	return (EXIT_SUCCESS);
}
