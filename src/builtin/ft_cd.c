/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:05:21 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 15:08:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_path_exist(t_var *var)
{
	if (cd_cdpath_application(var) == 1)
	{	
		free_cd_path(var);
		return (1);
	}
	if (access(var->cd->cdpath, F_OK) == 0 && var->input->args[1] != 0)
	{
		free_cd_path(var);
		return (1);
	}
	return (0);
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
				&& ft_strlen(var->input->args[1]) == 1))
			return (2);
	}
	if (var->input->args[1] != 0 && var->cd->cdpath != 0)
		var->cd->cdpath = ft_strjoin(var->cd->cdpath, var->input->args[1]);
	if (cd_path_exist(var) == 1)
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
	if (i == 1 || var->cd->cdpath_exist == 1)
	{
		if (i == 1)
			EXIT_STATUS = 1;
		if (var->cd->cdpath_exist == 1)
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
