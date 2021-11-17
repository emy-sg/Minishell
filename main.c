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

void	catch_int(int sig)
{
	if (global.global == 1)
	{
		(void)sig;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
	}
	else
	{
		(void)sig;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	catch_quit(int sig)
{
	if (global.global == 1)
	{
		rl_replace_line("", 0);
		printf("Quit:3");
	}
	if (global.global == 0)
	{
		(void)sig;
		
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **arge)
{
	char			*cmdline_buf;
	t_env_export	*env_export;
	t_lexer			*s_lexer;
	
	global.global = 0;	
	signal(SIGINT, catch_int);
	signal(SIGQUIT, catch_quit);
	env_export = init_env_export((const char **)arge);
	while (1)
	{
		(void)argc;
		(void)*argv;
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
		//system("leaks minishell");
	}
	clear_history();
	return (0);
}
