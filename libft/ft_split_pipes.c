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

static int	is_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

void check_Quotes(const char *str, size_t i, _Bool *simple_quote, _Bool *double_quote)
{
	if (str[i] == '"' && *simple_quote == FALSE)
	{
		if (*double_quote == FALSE)
			*double_quote = TRUE;
		else
			*double_quote = FALSE;
	}
	else if (str[i] == '\'' && *double_quote == FALSE)
	{
		if (*simple_quote == FALSE)
			*simple_quote = TRUE;
		else
			*simple_quote = FALSE;
	}
}

int count_charset_pipe(const char *str, char c, _Bool *simple_quote, _Bool *double_quote)
{
	_Bool is_word;
	int count_words;
	size_t	i;

	is_word = TRUE;
	count_words = 0;
	i = -1;
	while (str[++i])
	{
		check_Quotes(str, i, simple_quote, double_quote);
		if (is_charset(str[i], c) && *double_quote == FALSE && *simple_quote == FALSE)
			is_word = TRUE;
		else if (is_word == TRUE)
		{
			count_words++;
			is_word	= FALSE;
		}
	}
	return (count_words);
}

int	ft_count_words(char const *str, char c)
{
	int total_words;
	_Bool simple_quote;
	_Bool double_quote;

	simple_quote = FALSE;
	double_quote = FALSE;
	total_words = 0;
	total_words += count_charset_pipe(str, c, &simple_quote, &double_quote);
	return (total_words);
}

int	ft_free_tab(char **str, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i > size)
		free(str[i++]);
	free(str);
	return (1);
}

size_t ft_pipe_strlen(const char *str, char c)
{
	size_t	len;
	_Bool	simple_quote;
	_Bool	double_quote;

	len = -1;
	simple_quote = FALSE;
	double_quote = FALSE;
	while (str[++len])
	{
		check_Quotes(str, len, &simple_quote, &double_quote);
		if (is_charset(str[len], c) && simple_quote == FALSE && double_quote == FALSE)
			return (len);
	}
	return (len);
}

int do_pipe_split(const char *s, char c, char **tab)
{
	int words;
	int i;
	int j;
	int len;

	i = -1;
	words = ft_count_words(s, c);
	while (++i < words)
	{
		j = 0;
		while (*s && is_charset(*s, c))
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
	char **tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	if (do_pipe_split(s, c, tab) == 1)
		return (NULL);
	return (tab);
}
