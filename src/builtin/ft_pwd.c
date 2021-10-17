/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:39:06 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/16 18:25:41 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 1)
		{
			if (access(tmp->content, F_OK) == 0)
			{
				printf("%s\n", getcwd(0, 150));
				return (0);
			}
			if (access(tmp->content, F_OK) == -1)
				perror("Path is invalid");
		}
		tmp = tmp->next;
	}
	printf("%s\n", getcwd(0, 150));
	return (0);
}
