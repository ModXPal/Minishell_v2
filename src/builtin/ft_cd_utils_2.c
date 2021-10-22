/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:09:34 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/21 14:52:29 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	get_home_unset_cd(t_var *var)
{
	var->cd->HOME = ft_envar_find_content(var->envar, "HOME");
	return (0);
}

int	cd_content_equal_zero(t_var	*var)
{
	int		dir;
	char	*str;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = ft_envar_find_content(tmp2, "HOME");
	if (cd_str_and_path_not_set(var) == 0)
		return (1);
	dir = chdir(str);
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
	if ((str == cd_str_and_path_not_set(var)) == 0)
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

	tmp2 = var->envar;
	str = NULL;
	str = ft_envar_find_content(tmp2, "OLDPWD");
	dir = chdir (str);
	printf("%s\n", getcwd(0, 150));
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
