/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:22:26 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 14:22:27 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

int		*init_sort_table(const char **menv);
int		*sort_table(const char **menv);
char	**init_export(const char **menv);
int		ft_export(t_ast *s_ast, t_env_export *env_export);
int		add_to_export(t_ast *s_ast, t_env_export *env_export);
int		print_export(char **export);
int		update_export(char **export);
int		update_export_old_pwd(char **export);
int		update_export_pwd(char **export);
int		export_exist(char **export, char *variable_name);
int		update_arg_export(char **export, char *arg, char *variable_name);
int		add_arg_export(t_env_export *env_export, char *var_name, char *var_value);
int		add_env_export(t_env_export *env_export, char **temp);
int		push_arg_export(t_env_export *env_export, char *arg);
int		add_export(t_env_export *env_export, char *arg);
int		fill_export(const char **menv, char **export, int *sorted);
int		export_exist_try_1(char **export, char *variable_name);
int		export_exist_try_2(char **export, char *variable_name);
char	*export_arg(char *menv);
#endif
