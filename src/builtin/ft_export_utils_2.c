/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:04:04 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/06 17:44:10 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_name_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			break ;
		}
		i++;
	}
	return (i);
}

int	export_error_no_equal(t_var *var, char *content)
{
	int j;

	j = 0;
	while (content[j])
	{
		if (ft_isalnumqual(content[j]) == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		j++;
	}
	return (0);
}

int	export_error_handling(t_var *var, char *content)
{
	int		i;

	i = 1;
	if (var->input->args[1] == 0 || content[0] == 0)
		return (-1);
	if (content[0] == 0)
		return (-1);
	while (var->input->args[i])
	{
		if (var->input->args[i][0] == '=' && content[0] != '=')
			return (0);
		else if (ft_isdigit(content[0])
			|| content[0] == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		i++;
	}
	if (export_error_no_equal(var, content) == -1)
		return (-1);
	return (0);
}