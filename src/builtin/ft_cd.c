/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/19 14:31:20 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	errors_chdir_handling(int dir, t_var *var)
{
	t_list	*tmp;

	tmp = var->list;
	if (dir < 0)
	{
		write (2, "minishell: ", 12);
		write(2, tmp->content, ft_strlen(tmp->content));
		write (2, ": ", 3);
		write(2, tmp->next->content, ft_strlen(tmp->next->content));
		write (2, ": ", 3);
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
		return (1);
	if (tmp->next)
	{
		if ((ft_strncmp(tmp->next->content, ".", 1) == 0
				&& ft_strlen(tmp->next->content) == 1)
			|| (ft_strncmp(tmp->next->content, "..", 2) == 0
				&& ft_strlen(tmp->next->content) == 2)
			|| (ft_strncmp(tmp->next->content, "/", 1) == 0
				&& ft_strlen(tmp->next->content) == 1))
		{
			return (1);
		}
	}
	if (tmp->next != 0 && var->cd->cdpath != 0)
		var->cd->cdpath = ft_strjoin(var->cd->cdpath, tmp->next->content);
	if (cd_cdpath_application(var) == 1)
		return (1);
	return (0);
}

int	cd_application(t_var *var)
{
	if (var->list->next == 0)
	{
		if (cd_content_equal_zero(var) == 1)
			return (1);
	}
	else if (cd_dash_tild(var) == 0)
	{
		if (cd_content_equal_tild_dash(var) == 1)
			return (1);
	}
	else if (ft_strlen(var->list->next->content) == 1
		&& var->list->next->content[0] == '-')
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
	if (check_cdpath_exists(var) == 0)
		return (0);
	if (cd_application(var) == 1)
		return (1);
	return (0);
}
