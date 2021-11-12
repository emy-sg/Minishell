#ifndef REDIRECT_H
# define REDIRECT_H

//redirection.c
int	ft_redir(t_ast *s_ast, t_env_export *env_export);

//back_to_normal.c
int 		redir_in_back_to_normal(t_redirect *redirect);
int 		redir_out_back_to_normal(t_redirect *redirect);

//here_doc.c
char 		 *mini_gnl(void);
int  		here_doc(char *limiter);

//init_redirection.c
t_redirect 	*init_redirect(t_ast *s_ast);
void 		open_files(t_ast *s_ast, t_redirect *redirect);
int 		redir_fdin(t_redir *redir);
int 		redir_fdout(t_redir *redir);

//simple_redirection.c
int 		simple_redir_in(t_redirect *redirect, t_ast *s_ast);
int 		simple_redir_out(t_redirect *redirect, t_ast *s_ast);

#endif
