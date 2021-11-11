/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:21:46 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 14:21:48 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	valid_arg_exit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_fisdigit(arg[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_ast *s_ast)
{
	int	length;

	length = ft_fstrlen_double((const char **)(s_ast->argv + 1));
	printf("exit\n");
	if (length == 0)
		exit(g_status);
	else if (valid_arg_exit(s_ast->argv[1]) == EXIT_FAILURE)
	{
		prg_error(s_ast->argv[0], s_ast->argv[1], "numeric argument required");
		exit (255);
	}
	else if (length == 1)
		exit(ft_fatoi(s_ast->argv[1]));
	else
		return (prg_error(s_ast->argv[0], NULL,  "too many arguments"));
	return (EXIT_SUCCESS);
}
