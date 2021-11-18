/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:59:25 by emallah           #+#    #+#             */
/*   Updated: 2021/11/17 22:01:39 by isghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **arge)
{
	char			*cmdline_buf;
	t_env_export	*env_export;
	t_lexer			*s_lexer;
	
	signal(SIGINT, catch_int);
	signal(SIGQUIT, catch_quit);
	env_export = init_env_export((const char **)arge);
	while (1)
	{
		(void)argc;
		(void)*argv;
		global.global = 0;
		global.here_doc = 0;
		global.here_doc_exit = 0;
		cmdline_buf = readline("$ ");
		if (!cmdline_buf)
		{
			printf("exit\n");
			clear_history();
			exit(1);
		}
		if (cmdline_buf[0] != '\0')
		{
			add_history(cmdline_buf);
			s_lexer = init_lexer(cmdline_buf);
			parse_and_execute(s_lexer, env_export);
		}
		else
			free(cmdline_buf);
	}
	clear_history();
	return (0);
}
