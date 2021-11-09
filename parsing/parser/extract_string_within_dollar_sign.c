/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string_within_dollar_sign.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:28:44 by isghioua          #+#    #+#             */
/*   Updated: 2021/11/09 15:49:41 by isghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_string_within_dollar_sign(t_ast *s_cmd, char **str_before,
		char *content)
{
	char	**str;
	int		size;
	char	**new_args;
	int		i;
	int		j;
	int		x;

	if (ft_strchr(content, ' ') == 0)
		return (content);
	else
	{
		str = ft_split(content, ' ');
		free(content);
		content = NULL;
		size = get_size_of_table(str) - 1;
		i = get_size_of_table(s_cmd->argv) + size;
		j = get_size_of_table(s_cmd->argv) - 1;
		new_args = ft_realloc_table(s_cmd->argv, size);
		content = ft_strjoin(*str_before, str[0]);
		free(*str_before);
		*str_before = ft_strdup("");
		free(str[0]);
		new_args[j] = content;
		j++;
		
		x = 1;
		while (j < i)
		{
			new_args[j] = str[x];
			j++;
			x++;
		}
		free(str);
		s_cmd->argv = new_args;
	}
	return (ft_strdup(""));
}
