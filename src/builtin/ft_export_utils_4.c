/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:04:38 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/28 17:28:17 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_name_len(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var->equal_env = 1;
			break ;
		}
		i++;
	}
	return (i);
}

int	export_error_no_equal(t_var *var, char *content)
{
	int	j;

	j = 0;
	while (content[j])
	{
		if (content[j] == '=')
			break ;
		else if (ft_isalnumqual(content[j]) == 0)
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
	if (content[0] == '=')
	{
		unset_error_export_message(var, content);
		return (-1);
	}
	if (ft_isdigit(content[0]) || content[0] == 0)
	{
		unset_error_export_message(var, content);
		return (-1);
	}
	if (export_error_no_equal(var, content) == -1)
		return (-1);
	return (0);
}
