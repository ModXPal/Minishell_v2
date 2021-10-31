/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:29:41 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/29 17:20:06 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_dash_n(char **str)
{
	int	i;

	i = 0;
	if (str[1] == NULL)
		return (0);
	if (str[1][i] == '-')
	{
		i++;
		while (str[1][i] == 'n')
		{
			if (str[1][i + 1] == '\0'
				|| str[1][i + 1] == ' ')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_echo(t_var *var)
{
	int		i;
	int		ret;

	i = 0;
	ret = is_dash_n(var->input->args);
	if (ret == TRUE)
		i++;
	while ((var->input->args)[++i])
	{
		printf("%s", (var->input->args)[i]);
		if ((var->input->args)[i + 1])
			printf(" ");
	}
	if (ret == FALSE)
		printf("\n");
	exit (0);
}
