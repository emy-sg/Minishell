/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <emallah@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:08 by emallah           #+#    #+#             */
/*   Updated: 2021/11/15 15:39:12 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_export(char **export)
{
	int		i;

	i = 0;
	while (export[i])
	{
		if (ft_strbstr(export[i], "NaN") == NULL)
			printf("%s\n", export[i]);
		i++;
	}
}
