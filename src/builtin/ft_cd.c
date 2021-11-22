/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/22 12:08:56 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	errors_chdir_handling(int dir, t_var *var)
{
	if (dir < 0)
	{
		write (2, "minishell: ", 11);
		write(2, var->input->cmd, ft_strlen(var->input->cmd));
		write (2, ": ", 2);
		write(2, var->input->args[1], ft_strlen(var->input->args[1]));
		write (2, ": ", 2);
		perror("");
		return (1);
	}
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
	return (str);
}

int	check_cdpath_exists(t_var *var)
{
	t_list	*tmp;

	tmp = var->list;
	var->cd->cdpath = 0;
	var->cd->cdpath = ft_envar_find_content(var->envar, "CDPATH");
	if (var->cd->cdpath == 0)
		return (2);
	if (var->input->args[1])
	{
		if ((ft_strncmp(var->input->args[1], ".", 1) == 0
				&& ft_strlen(var->input->args[1]) == 1)
			|| (ft_strncmp(var->input->args[1], "..", 2) == 0
				&& ft_strlen(var->input->args[1]) == 2)
			|| (ft_strncmp(var->input->args[1], "/", 1) == 0
				&& ft_strlen(var->input->args[1]) == 1)
			|| (access(var->input->args[1], F_OK) == 0))
		{
			return (2);
		}
	}
	if (var->input->args[1] != 0 && var->cd->cdpath != 0)
		var->cd->cdpath = ft_strjoin(var->cd->cdpath, var->input->args[1]);
	if (cd_cdpath_application(var) == 1)
		return (1);
	return (0);
}

int	cd_application(t_var *var)
{
	if (var->input->args[1] == 0)
	{
		if (cd_content_equal_zero(var) == 1)
			return (1);
	}
	else if (cd_dash_tild(var) == 0)
	{
		if (cd_content_equal_tild_dash(var) == 1)
			return (1);
	}
	else if (ft_strlen(var->input->args[1]) == 1
		&& var->input->args[1][0] == '-')
	{
		if (cd_dash_equal_one(var) == 1)
			return (1);
	}
	else
	{
		if (swap_pwd_old_pwd(var) == 1)
			return (1);
	}
	return (0);
}

int	ft_cd(t_var *var)
{
	int	i;

	i = -1;
	if (cd_too_many_arguments(var) == 1)
	{
		cd_error_message_too_many_arguments(var);
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	i = check_cdpath_exists(var);
	if (i == 1)
	{
		if (i == 1)
			EXIT_STATUS = 1;
		if (i == 0)
			EXIT_STATUS = 0;
		return (EXIT_STATUS);
	}
	if (cd_application(var) == 1)
	{
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
