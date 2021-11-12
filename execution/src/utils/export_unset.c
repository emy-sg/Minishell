/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:08:50 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 15:08:52 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	valid_arg(char *arg)
{
	int	i;

	i = 1;
	if (!ft_fisalpha(arg[0]) && arg[0] != '_')
		return (EXIT_FAILURE);
	while (arg[i])
	{
		if (!ft_fisalnum(arg[i]) && arg[i] != '_' && arg[i] != '=' && arg[i] != ' ')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	valid_input(t_ast *s_ast)
{
	int	i;

	i = 1;
	while (s_ast->argv[i])
	{
		if (valid_arg(s_ast->argv[i]) == EXIT_FAILURE)
			prg_error(s_ast->argv[0], s_ast->argv[i], "not a valid identifier");
		i++;
	}
	return (EXIT_SUCCESS);
}
