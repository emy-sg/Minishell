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