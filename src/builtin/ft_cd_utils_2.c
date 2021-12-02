/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:00:14 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 16:55:59 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_content_equal_zero(t_var	*var)
{
	char	*str;
	t_envar	*tmp2;
	int		dir;

	tmp2 = var->envar;
	dir = 0;
	str = ft_envar_find_content(tmp2, "HOME");
	if (str != 0)
	{
		dir = chdir(str);
		if (dir < 0)
			return (-1);
	}
	if (cd_str_and_path_not_set(var) == 0)
		return (1);
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
		return (1);
	return (0);
}

int	cd_content_equal_tild_dash(t_var *var)
{
	int		dir;
	char	*str;

	dir = 0;
	str = 0;
	str = cd_str_and_path_not_set(var);
	if (str[0] == 0)
		return (1);
	dir = chdir(str);
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
	{
		return (1);
	}
	return (0);
}

char	*cd_str_and_path_oldpwd_not_set(t_var *var)
{
	char	*str;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = NULL;
	str = ft_envar_find_content(tmp2, "OLDPWD");
	if (str == 0)
	{
		write(2, "minishell: cd:", 14);
		ft_putendl_fd(" OLDPWD not set", 2);
		return (0);
	}
	return (str);
}

int	cd_dash_equal_one(t_var *var)
{
	int		dir;
	char	*str;
	t_envar	*tmp2;
	char	*current_path;

	tmp2 = var->envar;
	str = NULL;
	current_path = NULL;
	str = cd_str_and_path_oldpwd_not_set(var);
	if (str == 0)
		return (1);
	str = ft_envar_find_content(tmp2, "OLDPWD");
	str = cd_str_and_path_not_set(var);
	dir = chdir (str);
	current_path = getcwd(NULL, 0);
	printf("%s\n", current_path);
	if (current_path)
		free(current_path);
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
		return (1);
	return (0);
}
