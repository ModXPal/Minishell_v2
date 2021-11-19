/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:09:34 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/17 14:39:36 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_content_equal_zero(t_var	*var)
{
	char	*str;
	t_envar	*tmp2;
	int		dir;

	tmp2 = var->envar;
	str = ft_envar_find_content(tmp2, "HOME");
	dir = chdir(str);
	if (cd_str_and_path_not_set(var) == 0)
		return (1);
	if (dir < 0)
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
		return (1);
	return (0);
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
	str = ft_envar_find_content(tmp2, "OLDPWD");
	dir = chdir (str);
	current_path = getcwd(0, 150);
	printf("%s\n", current_path);
	if (current_path)
		free(current_path);
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
		return (1);
	return (0);
}

int	cd_dash_tild(t_var *var)
{
	if ((ft_strncmp(var->input->args[1], "--", 3) == 0
			&& ft_strlen(var->input->args[1]) == 2))
	{
		return (0);
	}
	return (1);
}
