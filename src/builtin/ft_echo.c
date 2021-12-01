/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:29:41 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/26 12:53:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_dash_n(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
		{
			if (str[i + 1] == '\0'
				|| str[i + 1] == ' ')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	echo_execution(t_var *var, int *ret, int *dash_n)
{
	int	i;

	i = 1;
	while ((var->input->args[i]))
	{
		if (is_dash_n(var->input->args[i]) == 1 && (*ret) == 0)
		{
			(*dash_n) = 1;
			i++;
		}
		else
		{
			printf("%s", var->input->args[i]);
			if ((var->input->args)[i + 1])
				printf(" ");
			(*ret) = 1;
			i++;
		}
	}
	return (0);
}

int	echo_args1_equal_zero(t_var *var)
{
	if ((var->input->args)[1] == NULL)
	{
		EXIT_STATUS = 0;
		printf("\n");
		return (EXIT_STATUS);
	}
	return (1);
}

int	echo_dollar_question(t_var *var)
{
	if (ft_strcmp(var->input->args[1], "$?") == 1
		&& ft_strlen(var->input->args[1]) == 2)
	{
		printf("%d\n", EXIT_STATUS);
		EXIT_STATUS = 0;
		return (EXIT_STATUS);
	}
	return (1);
}

int	ft_echo(t_var *var)
{
	int		ret;
	int		dash_n;

	ret = 0;
	dash_n = 0;
	if (echo_args1_equal_zero(var) == 0)
		return (EXIT_STATUS);
	if (echo_dollar_question(var) == 0)
		return (EXIT_STATUS);
	echo_execution(var, &ret, &dash_n);
	if (ret == 1 && dash_n == 0)
		printf("\n");
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
