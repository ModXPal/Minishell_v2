/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:05:14 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 12:09:13 by                  ###   ########.fr       */
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
		g_exit_status = 1;
		perror("pwd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return (g_exit_status);
	}
	printf("%s\n", test);
	if (test != 0)
		free (test);
	g_exit_status = 0;
	return (g_exit_status);
}
