/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:37:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 18:01:37 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



char	*ft_trim(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;
	char	*envar;

	trim_str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!trim_str || len == 0)
	{
		free(trim_str);
		return (NULL);
	}
	j = 0;
	i = 0;
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
		trim_str[i++] = str[j++];
	}
	return (trim_str);
}
