/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:41:26 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 14:39:22 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	check_access(t_pvar *pvar, int i)
{
	if (pvar->path[0][0] == '\0')
		return (0);
	if (pvar->cmd == 0)
		return (0);
	if (i == -1)
	{
		if (access(pvar->cmd, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	else if (access(pvar->cmd, X_OK) == -1 && pvar->path[i + 1] == 0)
		return (0);
	else if (access(pvar->cmd, X_OK) == 0)
		return (1);
	return (-1);
}

int	check_relative_exec(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "./", 2) == 0)
		return (1);
	if (ft_strncmp(str, "../", 3) == 0)
		return (2);
	return (0);
}

int	get_prog_path(t_pvar *pvar, t_var *var)
{
	if (check_relative_exec(var->input->cmd) == 1)
	{
		pvar->cmd = ft_strdup(&(var->input->cmd[2]));
		return (0);
	}
	else if (check_relative_exec(var->input->cmd) == 2)
	{
		pvar->cmd = ft_strdup(var->input->cmd);
		return (0);
	}
	return (1);
}

int	executable_error(t_var *var, t_pvar *pvar)
{
	DIR	*dir;

	(void)var;
	if (access(pvar->cmd, X_OK) == -1)
	{
		write (2, "minishell: ", 11);
		perror(pvar->cmd);
		g_exit_status = 127;
		return (0);
	}
	dir = opendir(pvar->cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pvar->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_exit_status = 127;
		return (0);
	}
	return (1);
}
