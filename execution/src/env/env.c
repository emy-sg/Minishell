/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:45:06 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:45:08 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	env(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = get_cmd_path("env", env);
	if (path == NULL)
		return (prg_error("env", NULL, "command not found"));
	while (env[i])
	{
		if (ft_strbstr(env[i], "NaN") == NULL)
			printf("%s\n", env[i]);
		i++;
	}
	free(path);
	return (EXIT_SUCCESS);
}
