/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:53:42 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 16:37:16 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_unmatched_quotes(t_var *var)
{
	int	i;
	int	d_quote_count;
	int	s_quote_count;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote_count = 0;
	s_quote_count = 0;
	d_quote = 0;
	s_quote = 0;
	while (var->cmd[++i])
	{
		if (var->cmd[i] == '"' && s_quote == FALSE)
		{
			check_d_quote(&d_quote);
			d_quote_count++;
		}
		if (var->cmd[i] == '\'' && d_quote == FALSE)
		{
			check_s_quote(&s_quote);
			s_quote_count++;
		}
	}
	return (d_quote_count % 2 + s_quote_count % 2);
}
