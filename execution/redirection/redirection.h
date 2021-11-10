#ifndef REDIRECT_H
# define REDIRECT_H

t_redirect	*init_redirect(t_ast *s_ast);
char *mini_gnl(void);
int here_doc(char *limiter);
int	redir_fdin(t_redir *redir);
int	redir_fdout(t_redir *redir);
int	simple_redir_in(t_redirect *redirect, t_ast *s_ast);
int	simple_redir_out(t_redirect *redirect, t_ast *s_ast);
int	redir_in_back_to_normal(t_redirect *redirect, t_ast *s_ast);
int	redir_out_back_to_normal(t_redirect *redirect, t_ast *s_ast);
int	simple_redir(t_ast *s_ast, t_env_export *env_export);

#endif
