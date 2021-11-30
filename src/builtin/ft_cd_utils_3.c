/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:03 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 11:20:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_cdpath_application(t_var *var)
{
	int		dir;
	char	*str;
	t_envar	*tmp2;
	char	*to_free;

	str = NULL;
	tmp2 = var->envar;
	dir = chdir(var->cd->cdpath);
	if (dir < 0)
	{
		errors_chdir_handling(dir, var);
		return (1);
	}
	var->cd->cdpath_exist = 1;
	str = ft_env_new_pwd(var, "PWD");
	to_free = getcwd(NULL, 0);
	printf("%s\n", to_free);
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, "PWD");
	ft_export_old_pwd(var, "OLDPWD", str);
	if (to_free)
		free (to_free);
	return (0);
}

int	swap_pwd_old_pwd_and_errors(t_var *var, char *current_path, int dir)
{
	current_path = ft_env_new_pwd(var, current_path);
	ft_env_old_pwd(var, "OLDPWD", current_path);
	current_path = ft_export_new_pwd(var, current_path);
	ft_export_old_pwd(var, "OLDPWD", current_path);
	if (errors_chdir_handling(dir, var) == 1)
		return (1);
	return (0);
}

int	swap_pwd_with_args(t_var *var, t_envar *tmp, char *current_path)
{
	if (var->input->args[1] != 0)
	{
		if (ft_strlen(var->input->args[1]) == 2
			&& (ft_strncmp(var->input->args[1], "//", 2) == 0))
		{
			if (tmp)
				tmp->content = current_path;
		}
		else
		{
			if (tmp)
				tmp->content = current_path;
		}
	}
	else
	{
		if (tmp)
			tmp->content = current_path;
	}
	return (0);
}

char	*ft_env_new_pwd_2(t_var *var, t_envar *tmp, char *str2, char *str)
{
	char	*to_free;

	if (tmp)
		to_free = tmp->content;
	else
		to_free = NULL;
	swap_pwd_with_args(var, tmp, str2);
	return (str);
}

int	cd_too_many_arguments(t_var *var)
{
	int	i;

	i = 0;
	while (var->input->args[i])
		i++;
	if (i > 2)
		return (1);
	else
		return (0);
}
