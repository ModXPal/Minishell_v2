/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:01:24 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/18 17:39:13 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "struct.h"
#include "../libft/libft.h"

int		is_dash_n(t_var *var);
int		ft_echo(t_var *var);
int		ft_env(t_var *var);
int		ft_exit(t_var *var);
int		ft_pwd(t_var *var);
int		ft_unset(t_var *var);
int		ft_cd(t_var *var);
int		ft_export(t_var *var);
int		ft_unset(t_var *var);
int		ft_execve(t_var *var);
int		ft_multipipes(t_var *var);
int		cmd_export_alone(t_var *var);
char	*export_name_equal_search(char *str, int *i, int *equal, char *name);
char	*export_content_search(int *i, char *str, char *content);
char	*ft_export_new_pwd(t_var *var, char *str);
void	ft_export_old_pwd(t_var *var, char *str, char *str2);
int		swap_pwd_old_pwd(t_var *var);
char	*ft_env_new_pwd(t_var *var, char *str);
int		errors_chdir_handling(int dir, t_var *var);
void	ft_env_old_pwd(t_var *var, char *str, char *str2);
int		unset_export_error_handling(t_var *var, char *content);
int		parsing_child(t_var *var);
void	parsing_parent(t_var *var, int parent);
char	*cd_str_and_path_not_set(t_var *var);
int		get_home_unset_cd(t_var *var);
int		cd_content_equal_tild_dash(t_var *var);
int 	cd_content_equal_zero(t_var *var);
int		cd_dash_equal_one(t_var *var);
int		unset_error_export_message(t_var *var, char *content);
int		check_cdpath_exists(t_var *var);
int		cd_application(t_var *var);
int		cd_dash_tild(t_var *var);
int		swap_pwd_old_pwd_and_errors(t_var *var, char *str, int dir);
int		cd_cdpath_application(t_var *var);
char	*cd_str_and_path_not_set(t_var *var);


#endif
