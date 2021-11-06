/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:22:30 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 14:22:32 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_export(t_ast *s_ast, t_env_export *env_export)
{
	if (s_ast->argv[1] == NULL)
		return (print_export(env_export->export));
	else
		return (add_to_export(s_ast, env_export));
	return (EXIT_SUCCESS);
}

int	print_export(char **export)
{
	int		i;

	i = 0;
	while (export[i])
	{
		if (ft_strbstr(export[i], "NaN") == NULL)
			printf("%s\n", export[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	add_to_export(t_ast *s_ast, t_env_export *env_export)
{
	int		i;
	char	**temp;

	i = 1;
	while (s_ast->argv[i])
	{
		if (valid_arg(s_ast->argv[i]) == EXIT_SUCCESS)
		{
			if (ft_fstrnstr(s_ast->argv[i], "=", 1))
			{
				temp = ft_fsplite(s_ast->argv[i], '=');
				if (temp == NULL)
					return (EXIT_FAILURE);
				if (add_env_export(env_export, temp) == EXIT_FAILURE)
					return (sys_error(s_ast->argv[0], s_ast->argv[i]));
			}
			else if (add_export(env_export, s_ast->argv[i]) == EXIT_FAILURE)
				return (sys_error(s_ast->argv[0], s_ast->argv[i]));
		}
		i++;
	}
	return (valid_input(s_ast));
}


 