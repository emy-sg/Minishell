/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:41:17 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:41:19 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_echo(t_ast *s_ast)
{
	int	i;

	i = 1;
	if (s_ast->argv[1] && ft_strbstr(s_ast->argv[1], "-n"))
		i = 2;
	while (s_ast->argv[i])
	{
		printf("%s", s_ast->argv[i]);
		if (s_ast->argv[++i])
			printf(" ");
	}
	if (s_ast->argv[1] && ft_strbstr(s_ast->argv[1], "-n") == NULL)
		printf("\n");
	return (EXIT_SUCCESS);
}
