/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:08:16 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/29 15:18:43 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int EXIT_STATUS;

char	*ft_export_new_pwd(t_var *var, char *str)
{
	char	*str2;
	t_envar	*tmp;

	tmp = var->export;
	str2 = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD"))
		{
			str = tmp->content;
			break ;
		}
		tmp = tmp->next;
	}
	str2 = getcwd(0, 150);
	str = ft_env_new_pwd_2(var, tmp, str2, str);
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

char	*ft_env_new_pwd(t_var *var, char *str)
{
	char	*str2;
	t_envar	*tmp;

	tmp = var->envar;
	str2 = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD"))
		{
			str = tmp->content;
			break ;
		}
		tmp = tmp->next;
	}
	str2 = getcwd(0, 150);
	str = ft_env_new_pwd_2(var, tmp, str2, str);
	return (str);
}

void	ft_env_old_pwd(t_var *var, char *str, char *str2)
{
	t_envar	*tmp;

	(void) str;
	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD"))
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
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = NULL;
	str = getcwd(0, 150);
	dir = chdir(var->input->args[1]);
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
	{
		if (str)
			free(str);
		return (1);
	}
	if (str)
		free(str);
	return (0);
}
