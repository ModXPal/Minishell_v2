/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:45:48 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 18:46:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset_first_letter(t_var *var, char *content, int i)
{
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
	return (0);
}

int	unset_not_alnum(t_var *var, char *content, int j)
{
	j++;
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

int	unset_export_error_handling(t_var *var, char *content)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (unset_first_letter(var, content, i) == -1)
		return (-1);
	if (unset_not_alnum(var, content, j) == -1)
		return (-1);
	return (0);
}
