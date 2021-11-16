/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:51:17 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/05 20:03:26 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_charset_pipe(const char *str, char c,
		_Bool *s_quote, _Bool *d_quote)
{
	_Bool	is_word;
	int		count_words;
	size_t	i;

	is_word = TRUE;
	count_words = 0;
	i = -1;
	while (str[++i])
	{
		check_split_quotes(str, i, s_quote, d_quote);
		if (is_sep(str[i], c) && *d_quote == FALSE && *s_quote == FALSE)
			is_word = TRUE;
		else if (is_word == TRUE)
		{
			count_words++;
			is_word = FALSE;
		}
	}
	return (count_words);
}

size_t	ft_count_words(char const *str, char c)
{
	int		total_words;
	_Bool	simple_quote;
	_Bool	double_quote;

	simple_quote = FALSE;
	double_quote = FALSE;
	total_words = 0;
	total_words += count_charset_pipe(str, c, &simple_quote, &double_quote);
	return (total_words);
}

size_t	ft_pipe_strlen(const char *str, char c)
{
	size_t	len;
	_Bool	s_quote;
	_Bool	d_quote;

	len = -1;
	s_quote = FALSE;
	d_quote = FALSE;
	while (str[++len])
	{
		check_split_quotes(str, len, &s_quote, &d_quote);
		if (is_sep(str[len], c) && s_quote == FALSE && d_quote == FALSE)
			return (len);
	}
	return (len);
}

int	do_pipe_split(const char *s, char c, char **tab)
{
	size_t	words;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	words = ft_count_words(s, c);
	while (++i < words)
	{
		j = 0;
		while (*s && is_sep(*s, c))
			s++;
		len = ft_pipe_strlen(s, c);
		tab[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!tab[i])
			return (ft_free_tab(tab, i));
		while (j < len)
			tab[i][j++] = *s++;
		tab[i][j] = 0;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_pipes(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	if (do_pipe_split(s, c, tab) == 1)
		return (NULL);
	return (tab);
}
