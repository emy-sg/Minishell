/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <emallah@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:44:02 by emallah           #+#    #+#             */
/*   Updated: 2021/11/15 15:44:04 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	run_cmd(t_ast *s_ast, t_env_export *env_export)
{
	char	*the_cmd;

	if (s_ast->argv[0][0] == '/'
		|| (s_ast->argv[0][0] == '.' && s_ast->argv[0][1] == '/'))
		the_cmd = ft_fstrdup(s_ast->argv[0]);
	else
		the_cmd = get_cmd_path(s_ast->argv[0], env_export->env);
	if (the_cmd == NULL)
	{
		free(the_cmd);
		prg_error(s_ast->argv[0], NULL, "command not found");
		exit(127);
	}
	if (execve(the_cmd, s_ast->argv, env_export->env) == -1)
		exit(1);
}

char	*try_all_paths(char **all_paths, char *cmd)
{
	int		i;
	char	*path_w_slash;
	char	*candidate_path;

	i = 0;
	while (all_paths[i])
	{
		path_w_slash = ft_fstrjoin(all_paths[i], "/");
		if (path_w_slash == NULL)
			return (NULL);
		candidate_path = ft_fstrjoin(path_w_slash, cmd);
		free(path_w_slash);
		if (candidate_path == NULL)
			return (NULL);
		if (access(candidate_path, F_OK) == 0)
			return (candidate_path);
		free(candidate_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**all_paths;
	char	*cmd_path;

	i = 0;
	all_paths = NULL;
	while (env[i])
	{
		if (ft_strbstr(env[i], "PATH="))
		{
			all_paths = ft_fsplit(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (all_paths == NULL)
		return (NULL);
	cmd_path = try_all_paths(all_paths, cmd);
	free_double(all_paths);
	return (cmd_path);
}
