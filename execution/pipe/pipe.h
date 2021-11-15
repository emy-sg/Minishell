#ifndef PIPE_H
# define PIPE_H

int	ft_cmd_pipe(t_ast *s_ast, t_env_export *env_export, char *heredoc_file_name);
int nbr_here_doc_all_cmd(t_ast *s_ast);
char    *here_doc_file_name_gen(int j);
char **heredoc_files_names_all_cmd(t_ast *s_ast);
int exec_here_doc_all_cmd(t_ast *s_ast, char **heredoc_files_names);
int	ft_pipe(t_ast *s_ast, t_env_export *env_export);

#endif
