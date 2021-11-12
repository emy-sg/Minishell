/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emallah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:01:51 by emallah           #+#    #+#             */
/*   Updated: 2021/11/02 15:01:52 by emallah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

//unset.c
int	unset(t_ast *s_ast, t_env_export *env_export);

//unset_env_export.c
int	unset_env_export(t_ast *s_ast, t_env_export *env_export);
int	remove_arg_env(t_env_export *env_export, char *arg);
int	remove_arg_export(t_env_export *env_export, char *arg);
int	delete_export_elements(char **export, char *temp);
int	remove_arg_env_export(t_env_export *env_export, char *arg);
#endif
