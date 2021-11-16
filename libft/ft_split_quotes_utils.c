/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:37:30 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 10:38:16 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int	ft_free_tab(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i > size)
		free(str[i++]);
	free(str);
	return (1);
}

int	check_redir(const char *str, size_t *i, _Bool *s_quote, _Bool *d_quote)
{
	if (*i == 0 && *s_quote == FALSE && *d_quote == FALSE)
	{
		while (str[*i] == '>')
		{
			(*i)++;
			if (str[(*i)] != '>')
				return (1);
		}
		while (str[*i] == '<')
		{
			(*i)++;
			if (str[(*i)] != '<')
				return (1);
		}
	}
	else if ((str[*i] == '>' || str[*i] == '<')
		&& *s_quote == FALSE && *d_quote == FALSE)
		return (1);
	return (0);
}

int	count_redir(const char *str, size_t *i, _Bool *is_word, int *count_words)
{
	if (is_sep(str[*i], '>'))
	{
		while (is_sep(str[*i + 1], '>'))
			(*i)++;
		*is_word = TRUE;
		(*count_words)++;
		return (1);
	}
	else if (is_sep(str[*i], '<'))
	{
		while (is_sep(str[*i + 1], '<'))
			(*i)++;
		*is_word = TRUE;
		(*count_words)++;
		return (1);
	}
	return (0);
}

size_t	count_charset(const char *str, char c, _Bool *s_quote, _Bool *d_quote)
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
		if (*s_quote == FALSE && *d_quote == FALSE)
		{
			if (count_redir(str, &i, &is_word, &count_words) == 1)
				continue ;
		}
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
