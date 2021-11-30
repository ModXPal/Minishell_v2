/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:39:06 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 11:20:49 by                  ###   ########.fr       */
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
	str = ft_envar_find_content(tmp, "PWD");
	test = getcwd(NULL, 0);
	if (test == NULL)
	{
		EXIT_STATUS = 1;
		perror("pwd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return (EXIT_STATUS);
	}
	printf("%s\n", test);
	if (test != 0)
		free (test);
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
