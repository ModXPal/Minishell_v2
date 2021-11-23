/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:03 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/22 12:07:15 by vbachele         ###   ########.fr       */
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
	{
		errors_chdir_handling(dir, var);
		return (1);
	}
	str = ft_env_new_pwd(var, "PWD");
	printf("%s\n", getcwd(0, 150));
	ft_env_old_pwd(var, "OLDPWD", str);
	str = ft_export_new_pwd(var, "PWD");
	ft_export_old_pwd(var, "OLDPWD", str);
	return (0);
}

int	swap_pwd_old_pwd_and_errors(t_var *var, char *current_path, int dir)
{
	current_path = ft_env_new_pwd(var, current_path); // = PWD
	ft_env_old_pwd(var, "OLDPWD", current_path);
	current_path = ft_export_new_pwd(var, current_path);
	ft_export_old_pwd(var, "OLDPWD", current_path);
	if (errors_chdir_handling(dir, var) == 1)
		return (1);
	return (0);
}

char	*ft_env_new_pwd_2(t_var *var, t_envar *tmp, char *str2, char *str)
{
	if (var->input->args[1] != 0)
	{
		if (ft_strlen(var->input->args[1]) == 2
			&& (ft_strncmp(var->input->args[1], "//", 2) == 0))
			tmp->content = "//";
		else
		{
			if (tmp)
				tmp->content = str2;
		}
	}
	else
	{
		if (tmp)
			tmp->content = str2;
	}
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

void	cd_error_message_too_many_arguments(t_var *var)
{
	write (2, "minishell: ", 11);
	write(2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": ", 2);
	write(2, var->input->args[1], ft_strlen(var->input->args[1]));
	write (2, ": too many arguments\n", 21);
}
