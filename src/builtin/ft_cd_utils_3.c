/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:03 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/22 15:14:42 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_cdpath_application(t_var *var)
{
	int		dir;
	char	*str;
	t_envar	*tmp2;

	str = NULL;
	tmp2 = var->envar;
	dir = chdir(var->cd->cdpath);
	if (dir < 0)
		return (1);
	str = ft_env_new_pwd(var, "PWD");
	printf("%s\n", var->cd->cdpath);
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, "PWD");
	ft_export_old_pwd(var, "OLDPWD", str);
	return (0);
}

int	swap_pwd_old_pwd_and_errors(t_var *var, char *str, int dir)
{
	str = ft_env_new_pwd(var, str);
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, str);
	ft_export_old_pwd(var, "OLDPWD", str);
	if (errors_chdir_handling(dir, var) == 1)
		return (1);
	return (0);
}
