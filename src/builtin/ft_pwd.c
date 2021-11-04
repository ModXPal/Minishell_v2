/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:39:06 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/04 11:10:49 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_var *var)
{
	t_envar	*tmp;
	char	*str;
	char	*test;

	tmp = var->envar;
	str = NULL;
	test = NULL;
	str = ft_envar_find_content(tmp, "PWD");
	test = getcwd(0, 150);
	if (str && ft_strlen(str) == 2 && ft_strncmp(str, "//", 2) == 0)
	{
		printf("//\n");
	}
	else
	{
		printf("%s\n", test);
		free(test);
	}
	return (0);
}
