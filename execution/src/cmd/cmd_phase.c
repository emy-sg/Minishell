#include "../../../minishell.h"

int ft_cmd_phase_1(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "cd"))
	{
		if (cd(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "pwd"))
	{
		if (print_pwd() == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int ft_cmd_phase_2(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "export"))
	{
		if (ft_export(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "env"))
	{
		if (env(env_export->env) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int ft_cmd_phase_3(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "unset"))
	{
		if (unset(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcstr(s_ast->argv[0], "echo"))
	{
		if (ft_echo(s_ast) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int ft_cmd_phase_4(t_ast *s_ast, t_env_export *env_export)
{
	if (ft_strcstr(s_ast->argv[0], "exit"))
	{
		if (ft_exit(s_ast) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	else
	{
		if (other(s_ast, env_export) == ERROR)
			return (sys_error(s_ast->argv[0], NULL));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}