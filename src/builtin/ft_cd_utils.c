/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:08:16 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/13 14:02:14 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_export_new_pwd(t_var *var, char *str)
{
	char	*str2;
	t_envar	*tmp;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			str = tmp->content;
			break ;
		}
		tmp = tmp->next;
	}
	str2 = getcwd(0, 150);
	tmp->content = str2;
	return (str);
}

void	ft_export_old_pwd(t_var *var, char *str, char *str2)
{
	t_envar	*tmp;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			tmp->content = str2;
			break ;
		}
		tmp = tmp->next;
	}
}

int	swap_pwd_old_pwd(t_var *var)
{
	int		dir;
	char	*str;

	str = NULL;
	dir = chdir(var->list->next->content);
	str = ft_env_new_pwd(var, "PWD");
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, "PWD");
	ft_export_old_pwd(var, "OLDPWD", str);
	if (dir < 0)
		errors_chdir_handling(dir);
	return (0);
}
