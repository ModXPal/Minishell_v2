/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:39:06 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/21 11:35:20 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_var *var)
{
	t_envar	*tmp;
	char	*str;

	tmp = var->envar;
	str = NULL;
	// while (tmp)
	// {
	// 	if (ft_strcmp(tmp->name, "PWD") == 1)
	// 	{
	// 		if (access(tmp->content, F_OK) == 0)
	// 		{
	// 			printf("%s\n", getcwd(0, 150));
	// 			return (0);
	// 		}
	// 		if (access(tmp->content, F_OK) == -1)
	// 			perror("Path is invalid");
	// 	}
	// 	tmp = tmp->next;
	// }
	str = ft_envar_find_content(tmp, "PWD");
	if (str && ft_strlen(str) == 2 && ft_strncmp(str, "//", 2) == 0)
	{
		printf("//\n");
	}
	else
		printf("%s\n", getcwd(0, 150));
	return (0);
}
