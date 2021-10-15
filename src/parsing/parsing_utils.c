/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:26:25 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 16:34:59 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_alnum(char *str, int *j)
{
	while (ft_isalnum(str[*j]) == TRUE)
		(*j)++;
}

int	is_valid_dollar(char *str, int i)
{
	if (str[i] == '$')
	{
		if (ft_isalnum(str[i + 1]))
			return (1);
	}
	return (0);
}

void	check_s_quote(int *s_quote)
{
	if (*s_quote == FALSE)
		*s_quote = TRUE;
	else
		*s_quote = FALSE;
}

void	check_d_quote(int *d_quote)
{
	if (*d_quote == FALSE)
		*d_quote = TRUE;
	else
		*d_quote = FALSE;
}

int	check_quotes(char *str, int *j, t_var *var)
{
	if (str[*j] == '"' && var->s_quote == FALSE)
	{
		check_d_quote(&var->d_quote);
		(*j)++;
		return (1);
	}
	if (str[*j] == '\'' && var->d_quote == FALSE)
	{
		check_s_quote(&var->s_quote);
		(*j)++;
		return (1);
	}
	return (0);
}
