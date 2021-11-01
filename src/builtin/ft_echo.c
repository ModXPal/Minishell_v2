/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:29:41 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/01 17:20:47 by vbachele         ###   ########.fr       */
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
	if (ft_strcmp(var->input->args[1], "$?") == 1 && ft_strlen(var->input->args[1]) == 2)
	{
		printf("%d\n", EXIT_STATUS);
		EXIT_STATUS = 0;
		exit (EXIT_STATUS);
	}
	while ((var->input->args)[++i])
	{
		printf("%s", (var->input->args)[i]);
		if ((var->input->args)[i + 1])
			printf(" ");
	}
	if (ret == FALSE)
		printf("\n");
	EXIT_STATUS = 0;
	exit (EXIT_STATUS);
}
