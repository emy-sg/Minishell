#include "../../../minishell.h"

int	add_to_export(t_ast *s_ast, t_env_export *env_export)
{
	int		i;
	char	**temp;

	i = 1;
	while (s_ast->argv[i])
	{
		if (valid_arg(s_ast->argv[i]) == EXIT_SUCCESS)
		{
			if (ft_fstrnstr(s_ast->argv[i], "=", 1))
			{
				temp = ft_fsplite(s_ast->argv[i], '=');
				if (temp == NULL)
					return (ERROR);
				if (add_env_export(env_export, temp) == ERROR)
					return (sys_error(s_ast->argv[0], s_ast->argv[i]));
			}
			else if (add_export(env_export, s_ast->argv[i]) == ERROR)
				return (sys_error(s_ast->argv[0], s_ast->argv[i]));
		}
		i++;
	}
	return (valid_input(s_ast));
}
