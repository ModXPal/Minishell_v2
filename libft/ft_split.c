/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:51:17 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/08 00:46:09 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static unsigned int	ft_ult_strlen(char const *str, char charset)
{
	unsigned int	i;

	i = 0;
	while (str[i] && !is_charset(str[i], charset))
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

static unsigned int	ft_count_words(char const *str, char charset)
{
	unsigned int	words_count;
	unsigned int	is_word;

	words_count = 0;
	is_word = 1;
	while (str && *str)
	{
		if (is_charset(*str, charset))
			is_word = 1;
		else if (is_word == 1)
		{
			words_count++;
			is_word = 0;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		str++;
	}
	return (words_count);
}

static char	**ft_free(char **str, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i > size)
		free(str[i++]);
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	int				j;
	unsigned int	i;
	unsigned int	words;

	if (!s)
		return (NULL);
	i = -1;
	tab = (char **)malloc(sizeof(*tab) * ((words = ft_count_words(s, c)) + 1));
	if (!tab)
		return (NULL);
	while (++i < words)
	{
		while (*s && is_charset(*s, c))
			s++;
		tab[i] = (char *)malloc(sizeof(**tab) * (ft_ult_strlen(s, c) + 1));
		if (!tab[i])
			return (ft_free(tab, i));
		j = 0;
		while (*s && !is_charset(*s, c))
		{
			if (*s == '"')
			{
				tab[i][j++] = *s++;
				while (*s != '"')
					tab[i][j++] = *s++;
			}
			if (*s == '\'')
			{
				tab[i][j++] = *s++;
				while (*s != '\'')
					tab[i][j++] = *s++;
			}
			tab[i][j++] = *s++;
		}
		tab[i][j] = 0;
	}
	tab[i] = 0;
	return (tab);
}
