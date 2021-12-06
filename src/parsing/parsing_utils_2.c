/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:32:29 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 14:41:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand_len(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (str[i + 1] == ' ')
			{
				i++;
				if (len != 0 && str[i - 1] == 0)
					len++;
			}
		}
		if (str[i])
			len++;
	}
	if (str[0] == ' ' || str[i - 1] == ' ')
		len++;
	printf("len = %d\n", len);
	return (len);
}

char	*trim_expand(char *str)
{
	int		len;
	int		i;
	char	*trim;

	i = -1;
	len = expand_len(str);
	trim = ft_calloc(sizeof(char), len + 1);
	if (trim == NULL)
		return (NULL);
	len = 0;
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (len != 0 && str[i - 1] == ' ')
			trim[len++] = ' ';
		trim[len++] = str[i];
	}
	if (str[0] == ' ' || str[i -1] == ' ')
		trim[len] = ' ';
	return (trim);
}

void	set_var(int *j, int *k, int i)
{
	*j = 0;
	*k = i;
}

char	*get_valid_envar(t_var *var, char *str, int i)
{
	t_envar	*tmp;
	int		j;
	int		k;

	tmp = var->envar;
	if (str[i] == '?')
		return (ft_itoa(g_exit_status));
	while (tmp)
	{
		set_var(&j, &k, i);
		while (tmp->name[j] && str[k] && ft_charcmp(tmp->name[j], str[k]))
		{
			j++;
			k++;
			if (tmp->name[j] == 0 && (str[k] == 0
					|| ((ft_isalnum(str[k]) == 0) && str[k] != '_')))
			{
				if (var->d_quote == FALSE)
					return (trim_expand(tmp->content));
				return (ft_strdup(tmp->content));
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	assign_envar(char *envar, char *trim_str, int *i)
{
	int	k;

	k = 0;
	while (envar && envar[k])
		trim_str[(*i)++] = envar[k++];
	if (envar)
	{
		free(envar);
		envar = NULL;
	}
}
