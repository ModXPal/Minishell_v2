/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:29:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/01 12:12:40 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_envar_len(int *j, int *i, t_var *var, char *str)
{
	char	*envar;

	envar = get_valid_envar(var, str, ++(*i));
	*j += ft_strlen(envar);
	if (envar)
		free (envar);
	if (str[*i] == '?')
		return ;
	while (ft_isalnum(str[*i]) == TRUE || str[*i] == '_')
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
