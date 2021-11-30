/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:08:16 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 18:53:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	str2 = getcwd(NULL, 0);
	str = ft_env_new_pwd_2(var, tmp, str2, str);
	return (str);
}

void	ft_export_old_pwd(t_var *var, char *str, char *str2)
{
	t_envar	*tmp;
	char	*to_free;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			to_free = tmp->content;
			tmp->content = str2;
			if (to_free && var->pwd_exist == 1)
			{
				free(to_free);
				to_free = NULL;
			}
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
			var->pwd_exist = 1;
			break ;
		}
		tmp = tmp->next;
	}
	str2 = getcwd(NULL, 0);
	str = ft_env_new_pwd_2(var, tmp, str2, str);
	return (str);
}

void	ft_env_old_pwd(t_var *var, char *str, char *str2)
{
	t_envar	*tmp;
	char	*to_free;

	(void) str;
	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD"))
		{
			to_free = tmp->content;
			tmp->content = str2;
			if (to_free && var->pwd_exist == 1)
			{
				free(to_free);
				to_free = NULL;
			}
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
	var->pwd_exist = 0;
	str = getcwd(NULL, 0);
	dir = chdir(var->input->args[1]);
	if (dir < 0)
	{
		errors_chdir_handling(dir, var);
		if (str && var->pwd_exist)
			free (str);
		return (1);
	}
	if (swap_pwd_old_pwd_and_errors(var, str, dir) == 1)
	{
		if (str && var->pwd_exist == 1)
			free (str);
		return (1);
	}
	if (str && var->pwd_exist == 1)
		free (str);
	return (0);
}
