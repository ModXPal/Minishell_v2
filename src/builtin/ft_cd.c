/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 15:16:10 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	errors_chdir_handling(int dir)
{
	if (dir < 0)
		perror("cd failed");
	// rajouter la fonction qui free
	return (0);
}

char	*ft_envar_swap_1(t_var *var, char *str)
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

void	ft_envar_swap_2(t_var *var, char *str, char *str2)
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

int	ft_cd(t_var *var)
{
	int		dir;
	t_list	*tmp;
	t_envar	*tmp2;
	char	*str;

	str = NULL;
	tmp2 = var->envar;
	tmp = var->list;
	tmp2 = var->envar;
	// if (var->cmd[3] == 0) // a modifier avec les bonnes valeurs
	// {
	// 	str = ft_envar_find_content(tmp2, "HOME");
	// 	dir = chdir(str);
	// 	str = ft_envar_swap_1(var, "PWD");
	// 	printf("%s\n", getcwd(0, 150));
	// 	return (0);
	// }
	dir = chdir(var->list->content);
	str = ft_envar_swap_1(var, "PWD");
	ft_envar_swap_2(var, "OLDPWD", str);
	if (dir < 0)
		errors_chdir_handling(dir);
	return (0);
}
