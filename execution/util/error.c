/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:17:43 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 13:17:45 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sys_error(char *cmd, char *arg)
{
	ft_putstr_fd("ok\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	//if (cmd && arg)
	//	printf("minishell: %s: %s: %s\n", cmd, arg, strerror(errno));
	//else if (cmd)
	//	printf("minishell: %s: %s\n", cmd, strerror(errno));
	//else if (arg)
	//	printf("minishell: %s: %s\n", arg, strerror(errno));
	//else
	//	printf("minishell: %s\n", strerror(errno));
	return (EXIT_SUCCESS);
}

int	prg_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("ok\n", 2);
	ft_putstr_fd(msg, 2);
	//if (arg)
	//	printf("minishell: %s: %s: %s\n", cmd, arg, msg);
	//else
	//	printf("minishell: %s: %s\n", cmd, msg);
	return (EXIT_SUCCESS);
}

int	prg_error_no_exit(char *cmd, char *msg)
{
	ft_putstr_fd("ok\n", 2);
	ft_putstr_fd(msg, 2);
	//printf("minishell: %s: %s\n", cmd, msg);
	return (EXIT_SUCCESS);
}
