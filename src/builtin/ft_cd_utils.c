/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:08:16 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/17 17:42:23 by vbachele         ###   ########.fr       */
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
	t_list	*tmp;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = NULL;
	tmp = var->list;
	dir = chdir(var->list->next->content);
	str = ft_env_new_pwd(var, "PWD");
	ft_env_old_pwd(var, "OLDPWD", str);
	if (errors_chdir_handling(dir, var) == 1)
		return (1);
	return (0);
}

char	*cd_str_and_path_not_set(t_var *var)
{
	char	*str;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = NULL;
	str = ft_envar_find_content(tmp2, "HOME");
	if (str == 0)
	{
		write(2, "minishell: cd:", 14);
		ft_putendl_fd(" HOME not set", 2);
		return (0);
	}
	// if (str[0] == 0)
	// 	exit(1);
	return (str);
}
