/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:01:24 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 15:15:27 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "struct.h"
#include "../libft/libft.h" 

int	is_dash_n(t_var *var);
int	ft_echo(t_var *var);
int	ft_env(t_var *var);
int	ft_exit(t_var *var);
int	ft_pwd(t_var *var);
int	ft_unset(t_var *var);
int	ft_cd(t_var *var);


#endif
