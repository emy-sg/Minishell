#ifndef REDIRECT_H
# define REDIRECT_H

//redirection.c
int	ft_redir(t_ast *s_ast, t_env_export *env_export, char *heredoc_file_name);

//back_to_normal.c
int 		redir_in_back_to_normal(t_redirect *redirect);
int 		redir_out_back_to_normal(t_redirect *redirect);

//here_doc.c
char 		 *mini_gnl(void);
int here_doc(char *limiter, char *heredoc_file_name);
int	cmd_has_here_doc(t_ast *the_cmd);
int	nbr_here_doc(t_ast *s_ast);

//init_redirection.c
t_redirect	*init_redirect(t_ast *s_ast, char *heredoc_file_name);
int	open_files(t_ast *s_ast, t_redirect *redirect, char *heredoc_file_name);
int         exec_here_doc(t_ast *s_ast, char *heredoc_file_name);

//simple_redirection.c
int 		simple_redir_in(t_redirect *redirect, t_ast *s_ast);
int 		simple_redir_out(t_redirect *redirect, t_ast *s_ast);

#endif
