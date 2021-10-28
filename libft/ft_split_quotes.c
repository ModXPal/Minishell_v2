/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:51:17 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/28 17:39:16 by rcollas          ###   ########.fr       */
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
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	//if (str[i] == '<' || str[i] == '>')
	//	return (1);
	while (str[i] && !is_charset(str[i], charset))
	{
		if (i != 0 && (str[i] == '<' || str[i] == '>'))
			break ;
		if (str[i] == '"' && s_quote == FALSE)
		{
			if (d_quote == FALSE)
				d_quote = TRUE;
			else
				d_quote = FALSE;
		}
		if (str[i] == '\'' && d_quote == FALSE)
		{
			if (s_quote == FALSE)
				s_quote = TRUE;
			else
				s_quote = FALSE;
		}
		while (str[i] == '>' && d_quote == FALSE && s_quote == FALSE) 
		{
			if (str[i + 1] == '<')
				return (i + 2);
			i++;
			if (str[i] != '>')
				return (i);
		}
		while (str[i] == '<' && d_quote == FALSE && s_quote == FALSE) 
		{
			if (str[i + 1] == '>')
				return (i + 2);
			i++;
			if (str[i] != '<')
				return (i);
		}
		i++;
	}
	printf("i2 = %d\n", i);
	return (i);
}

static unsigned int	ft_count_words(char const *str, char charset)
{
	unsigned int	words_count;
	unsigned int	is_word;
	int		s_quote;
	int		d_quote;

	words_count = 0;
	is_word = 1;
	s_quote = 0;
	d_quote = 0;
	while (str && *str)
	{
		if (*str == '<' && d_quote == FALSE && s_quote == FALSE)  
		{
			if (*(str + 1) == '>')
			{
				str += 2;
				words_count++;
			}
			else
			{
				while (*str == '<' && *str)
					str++;
				words_count++;
			}
		}
		else if (*str == '>' && d_quote == FALSE && s_quote == FALSE)  
		{
			if (*(str + 1) == '<')
			{
				str += 2;
				words_count++;
			}
			else
			{
				while (*str == '>' && *str)
					str++;
				words_count++;
			}
		}
		else if (is_charset(*str, charset) && s_quote == FALSE && d_quote == FALSE)
			is_word = 1;
		else if (is_word == 1)
		{
			words_count++;
			is_word = 0;
		}
		if (*str == '"' && s_quote == FALSE)
		{
			if (d_quote == FALSE)
				d_quote = TRUE;
			else
				d_quote = FALSE;
		
		}
		if (*str == '\'' && d_quote == FALSE)
		{
			if (s_quote == FALSE)
				s_quote = TRUE;
			else
				s_quote = FALSE;
			
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

char	**ft_split_quotes(char const *s, char c)
{
	char			**tab;
	int				j;
	unsigned int	i;
	unsigned int	words;
	int		len;

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
		len = ft_ult_strlen(s, c);
		tab[i] = (char *)malloc(sizeof(**tab) * (len + 1));
		if (!tab[i])
			return (ft_free(tab, i));
		j = 0;
		while (*s && j < len)
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
