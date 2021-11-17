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

void	missing_file(char *file)
{
	write (2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	write (2, ": No such file or directory\n", 28);
	EXIT_STATUS = 1;
}

void	permission_denied(char *file)
{
	write (2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	write (2, ": Permission denied\n", 20);
	EXIT_STATUS = 1;
}

int	pipe_error(void)
{
	write (2, "minishell: syntax error near unexpected token `", 47);
	write (2, "|", 1);
	write (2, "'\n", 2);
	EXIT_STATUS = 2;
	return (-1);
}

int	syntax_error(char **input, int i, int j)
{
	if (j == 2)
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][0], 2);
		write (2, "'\n", 2);
	}
	else if (j == 3)
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][0], ft_strlen(&input[i][0]));
		write (2, "'\n", 2);
	}
	else
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, "newline", 7);
		write (2, "'\n", 2);
	}
	EXIT_STATUS = 2;
	return (-1);
}
