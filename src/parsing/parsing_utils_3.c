/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:37:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/09 10:40:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	trim_str_len_is_null(char *trim_str, int len)
{
	if (!trim_str || len == 0)
	{
		free(trim_str);
		return (0);
	}
	return (1);
}

void	init(int *j, int *i)
{
	*j = 0;
	*i = 0;
}

char	*ft_trim(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;
	char	*envar;

	trim_str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (trim_str_len_is_null(trim_str, len) == 0)
		return (NULL);
	init(&j, &i);
	while (i < len)
	{
		if (check_quotes(str, &j, var) == TRUE)
			continue ;
		if (str[j] == '$' && var->s_quote == FALSE)
		{
			envar = get_valid_envar(var, str, ++j);
			assign_envar(envar, trim_str, &i);
			skip_alnum(str, &j);
			continue ;
		}
		if (!str[j])
			break ;
		trim_str[i++] = str[j++];
	}
	return (trim_str);
}
