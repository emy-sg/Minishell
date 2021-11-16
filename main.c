/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isghioua <isghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:59:25 by emallah           #+#    #+#             */
/*   Updated: 2021/11/16 22:43:40 by isghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_int(int sig)
{
	if (g_global == 1)
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
	if (g_global == 0)
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
	//////////////////////////////////
	struct	termios term;
	struct	termios init;

	g_global = 0;
	
	signal(SIGINT, catch_int);
	signal(SIGQUIT, catch_quit);

	if (tcgetattr(0, &term) == -1)
		return (-1);
	if (tcgetattr(0, &init) == -1)
		return(-1);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	char	*term_type = getenv("TERM");
	int		ret = tgetent(NULL, term_type);
	//////////////////////////////////////
	env_export = init_env_export((const char **)arge);
	while (1)
	{
		
		(void)argc;
		(void)*argv;
		cmdline_buf = readline("$ \033[s");
		// cmdline_buf = readline("$ ");
		if (!cmdline_buf)
		{
			//////////////////////////////////
			if (ret == -1 || ret == 0)
				printf("NULL\n");
			printf("\033[uexit\n");
			///////////////////////////////////
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
	//////////////////////////////////////////
	if(tcsetattr(0, TCSANOW, &init) == -1)
		return (-1);
	////////////////////////////////////////////
	clear_history();
	return (0);
}
