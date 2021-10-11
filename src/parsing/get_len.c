/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:29:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/11 20:31:03 by rcollas          ###   ########.fr       */
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
	while (str[++i])
	{
		if (check_quotes(str, &i, var) == TRUE)
			continue;
		if (str[i] == '$' && var->s_quote == FALSE && is_valid_dollar(str, i))
		{
			get_envar_len(&j, &i, var, str);
			continue ;
		}
		j++;
	}
	return (j);
}
