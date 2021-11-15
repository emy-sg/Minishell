#include "../../minishell.h"

t_redirect	*init_redirect(t_ast *s_ast, char *heredoc_file_name)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)ft_calloc(sizeof(t_redirect), 2);
	if (redirect == NULL)
	{
		sys_error(s_ast->argv[0], NULL);
		return (NULL);
	}
	redirect->stdout_fd = dup(1);
	redirect->stdin_fd = dup(0);
	redirect->fdin = 0;
	redirect->fdout = 0;
	redirect->here_doc_length = nbr_here_doc(s_ast);
	if (open_files(s_ast, redirect, heredoc_file_name) == ERROR)
		return (NULL);
	return (redirect);
}

int	open_files(t_ast *s_ast, t_redirect *redirect, char *heredoc_file_name)
{
	int			i;

	i = 0;
	while (s_ast->redir[i])
	{
		if (s_ast->redir[i]->type == INPUT_REDIR)
			redirect->fdin = open(s_ast->redir[i]->file_name, O_RDONLY, 0777);
		if (s_ast->redir[i]->type == HERE_DOC_REDIR)
			redirect->here_doc_length--;
		if (s_ast->redir[i]->type == OVERWRITE_REDIR )
			redirect->fdout = open(s_ast->redir[i]->file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (s_ast->redir[i]->type == APPEND_REDIR )
			redirect->fdout = open(s_ast->redir[i]->file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (redirect->here_doc_length == 0)
			redirect->fdin = open(heredoc_file_name, O_RDONLY, 0777);
		if (redirect->fdin == -1 || redirect->fdout == -1)
		{
			g_status = 1;
			return (sys_error(NULL, s_ast->redir[i]->file_name));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
