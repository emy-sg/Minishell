/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:32:13 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:32:15 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*cd_path(const char *arg, char **env)
{
	if (arg == NULL)
		return (home_path(env));
	else if (arg[0] == '/')
		return (path_w_slash(arg));
	return (abs_path(arg));
}

char	*path_w_slash(const char *arg)
{
	char	*path;

	path = ft_fstrdup(arg);
	if (path == NULL)
	{
		sys_error("cd", NULL);
		return (NULL);
	}
	return (path);
}

char	*home_path(char **env)
{
	int		i;
	char	**temp;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strbstr(env[i], "HOME="))
		{
			temp = ft_fsplit(env[i], '=');
			if (temp == NULL)
			{
				sys_error("cd", NULL);
				return (NULL);
			}
			path = ft_fstrdup(temp[1]);
			free_double(temp);
			if (path == NULL)
			{
				sys_error("cd", NULL);
				return (NULL);
			}
			return (path);
		}
		i++;
	}
	prg_error("cd", NULL, "HOME not set");
	return (NULL);
}

char	*abs_path(const char *arg)
{
	char	*path;
	char	*path_w_slash;
	char	*joined_path;

	path = pwd();
	if (path == NULL)
	{
		sys_error("cd", NULL);
		return (NULL);
	}
	path_w_slash = ft_fstrjoin(path, "/");
	free(path);
	if (path_w_slash == NULL)
	{
		sys_error("cd", NULL);
		return (NULL);
	}
	joined_path = ft_fstrjoin(path_w_slash, arg);
	free(path_w_slash);
	return (joined_path);
}

