/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:01:57 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 15:01:59 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	unset(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_fstrlen_double((const char **)s_ast->argv) > 1)
		return (unset_env_export(s_ast, env_export));
	return (EXIT_SUCCESS);
}
