/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:01:24 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/13 18:05:26 by vbachele         ###   ########.fr       */
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
int		ft_excve(t_var *var);
int		cmd_export_alone(t_var *var);
char	*export_name_equal_search(t_var *var, int *i, int *equal, char *name);
char	*export_content_search(int *i, char *str, char *content);
char	*ft_export_new_pwd(t_var *var, char *str);
void	ft_export_old_pwd(t_var *var, char *str, char *str2);
int		swap_pwd_old_pwd(t_var *var);
char	*ft_env_new_pwd(t_var *var, char *str);
int		errors_chdir_handling(int dir, t_var *var);
void	ft_env_old_pwd(t_var *var, char *str, char *str2);
int		unset_export_error_handling(t_var *var);

#endif
