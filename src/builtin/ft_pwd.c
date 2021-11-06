/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:39:06 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/06 16:07:25 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	if (test == NULL)
	{
		EXIT_STATUS = 1;
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (EXIT_STATUS);
	}
	if (str && ft_strlen(str) == 2 && ft_strncmp(str, "//", 2) == 0)
		printf("//\n");
	else
	{
		printf("%s\n", test);
		free(test);
	}
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
