/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:04:04 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/28 16:12:20 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_name_len(char *str)
{
	int	i;

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

int	exec_export(t_var *var, char *args)
{
	int		i;
	int		equal;
	int		j;

	i = 0;
	equal = 0;
	j = 0;
	var->name = ((char *)malloc(sizeof(char) * (export_name_len(args) + 1)));
	var->name = export_name_equal_search(var, args, &i, &equal);
	if (equal == 1)
		j = ft_strlen(args) - export_name_len(args);
	if (j > 0 && equal == 1)
	{
		var->content = ((char *) malloc(sizeof(char) * (j + 1)));
		var->content = export_content_search(var, &i, args);
	}
	i = export_env_reassigned_check(var, equal);
	if (equal == 1 && i != -1)
		export_env_insert(var);
	if (export_export_reassigned_check(var, equal) != -1)
		cmd_export_insert(var, equal);
	return (0);
}
