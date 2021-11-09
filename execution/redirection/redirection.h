#ifndef REDIRECT_H
# define REDIRECT_H

int	redir_out(t_ast *s_ast);
int	redir_in(t_ast *s_ast);
t_redirect	*init_redirect(t_ast *s_ast);
int	simple_redir(t_ast *s_ast, t_env_export *env_export);
int	simple_redir_in(t_redirect *redirect, t_ast *s_ast, t_env_export *env_export);
int	simple_redir_out(t_redirect *redirect, t_ast *s_ast, t_env_export *env_export);

#endif
