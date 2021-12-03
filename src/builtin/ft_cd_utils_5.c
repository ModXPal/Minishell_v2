/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:01:39 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 11:15:59 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	error_chdir(t_var *var, int dir, char *str)
{
	if (dir < 0)
	{
		errors_chdir_handling(dir, var);
		if (str && var->pwd_exist == 1)
			free (str);
		return (1);
	}
	return (0);
}

int	check_if_pwd_exist(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD"))
		{
			var->pwd_exist = 1;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD"))
		{
			var->oldpwd_exist = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	cd_path_deploying(t_var *var)
{
	int	i;

	i = -1;
	i = check_cdpath_exists(var);
	if (i == 1 || var->cd->cdpath_exist == 1)
	{
		if (i == 1)
			EXIT_STATUS = 1;
		if (var->cd->cdpath_exist == 1)
			EXIT_STATUS = 0;
		return (1);
	}
	return (0);
}
