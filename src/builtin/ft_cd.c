/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/13 15:23:26 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	errors_chdir_handling(int dir, t_var *var)
{
	t_list	*tmp;

	tmp = var->list;
	if (dir < 0)
		write (2, "minishell: ", 12);
		write(2, tmp->content, ft_strlen(tmp->content));
		write (2, ": ", 3);
		write(2, tmp->next->content, ft_strlen(tmp->next->content));
		write (2, ": ", 3);
		perror("");
	return (0);
}

char	*ft_env_new_pwd(t_var *var, char *str)
{
	char	*str2;
	t_envar	*tmp;

	tmp = var->envar;
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

void	ft_env_old_pwd(t_var *var, char *str, char *str2)
{
	t_envar	*tmp;

	tmp = var->envar;
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

int	cd_content_equal_zero(t_var *var)
{
	int		dir;
	char	*str;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = ft_envar_find_content(tmp2, "HOME");
	dir = chdir(str);
	str = ft_env_new_pwd(var, "PWD");
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, "PWD");
	ft_export_old_pwd(var, "OLDPWD", str);
	if (dir < 0)
		errors_chdir_handling(dir, var);
	return (0);
}

int	ft_cd(t_var *var)
{
	t_list	*tmp;
	t_envar	*tmp2;

	tmp2 = var->envar;
	tmp = var->list;
	tmp2 = var->envar;
	if (var->list->next == 0)
	{
		cd_content_equal_zero(var);
		return (0);
	}
	swap_pwd_old_pwd(var);
	return (0);
}
