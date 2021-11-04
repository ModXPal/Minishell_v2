/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:29:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/04 13:46:01 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_envar_len(int *j, int *i, t_var *var, char *str)
{
	*j += ft_strlen(get_valid_envar(var, str, ++(*i)));
	while (ft_isalnum(str[*i]) == TRUE)
		(*i)++;
	(*i)--;
}

int	get_string_len(char *str, t_var *var)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (str == NULL)
		return (0);
	while (str[++i])
	{
		if (check_quotes(str, &i, var) == TRUE)
		{
			i--;
			continue ;
		}
		if (str[i] == '$' && var->s_quote == FALSE && is_valid_dollar(str, i))
		{
			get_envar_len(&j, &i, var, str);
			continue ;
		}
		j++;
	}
	return (j);
}

int	get_heredoc_len(char *str, t_var *var)
{
	int	i;
	int	j;

	if (str == NULL)
		return (-1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && is_valid_dollar(str, i))
		{
			get_envar_len(&j, &i, var, str);
			continue ;
		}
		j++;
	}
	return (j);
}
