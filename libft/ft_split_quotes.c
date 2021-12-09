/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:51:17 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/09 10:36:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_split_quotes(const char *str, size_t i,
			_Bool *s_quote, _Bool *d_quote)
{
	if (str[i] == '"' && *s_quote == FALSE)
	{
		if (*d_quote == FALSE)
			*d_quote = TRUE;
		else
			*d_quote = FALSE;
	}
	else if (str[i] == '\'' && *d_quote == FALSE)
	{
		if (*s_quote == FALSE)
			*s_quote = TRUE;
		else
			*s_quote = FALSE;
	}
}

size_t	ft_ult_strlen(const char *str, char c)
{
	size_t	len;
	_Bool	s_quote;
	_Bool	d_quote;

	len = -1;
	s_quote = FALSE;
	d_quote = FALSE;
	while (str[++len])
	{
		if (check_redir(str, &len, &s_quote, &d_quote) == 1)
			return (len);
		check_split_quotes(str, len, &s_quote, &d_quote);
		if (is_sep(str[len], c) && s_quote == FALSE && d_quote == FALSE)
			return (len);
	}
	return (len);
}

size_t	count_words(const char *str, char c)
{
	size_t	total_words;
	_Bool	simple_quote;
	_Bool	double_quote;

	simple_quote = FALSE;
	double_quote = FALSE;
	total_words = 0;
	total_words += count_charset(str, c, &simple_quote, &double_quote);
	return (total_words);
}

int	do_split(const char *s, char c, char **tab)
{
	size_t	words;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	words = count_words(s, c);
	while (++i < words)
	{
		j = 0;
		while (*s && is_sep(*s, c))
			s++;
		len = ft_ult_strlen(s, c);
		tab[i] = (char *)ft_calloc(sizeof(char), (len + 1));
		if (!tab[i])
			return (ft_free_tab(tab, i));
		while (j < len)
			tab[i][j++] = *s++;
	}
	return (0);
}

char	**ft_split_quotes(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)ft_calloc(sizeof(char *), (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	if (do_split(s, c, tab) == 1)
		return (NULL);
	return (tab);
}
