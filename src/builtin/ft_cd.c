/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/18 15:39:44 by vbachele         ###   ########.fr       */
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

int	cd_dash_tild(t_var *var)
{
	t_list	*tmp;

	tmp = var->list;
	if ((var->list->next->content[0] == '-'
			&& var->list->next->content[1] == '-'
			&& ft_strlen(var->list->next->content) == 2)
		|| (var->list->next->content[0] == '~'))
	{
		return (0);
	}
	return (1);
}

int	ft_cd(t_var *var)
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
