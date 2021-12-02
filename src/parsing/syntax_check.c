#include "parsing.h"

int	check_pipes(t_var *var)
{
	int		i;
	_Bool	non_empty;

	i = -1;
	non_empty = FALSE;
	while (var->cmd[++i])
	{
		if (var->cmd[i] != ' ' && var->cmd[i] != '|')
			non_empty = TRUE;
		else if (non_empty == FALSE && var->cmd[i] == '|')
			return (pipe_error());
		else if (var->cmd[i] == '|')
			non_empty = FALSE;
	}
	if (non_empty == FALSE)
		return (-1);
	return (0);
}

int	check_unmatched_quotes(t_var *var)
{
	int	i;
	int	d_quote_count;
	int	s_quote_count;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote_count = 0;
	s_quote_count = 0;
	d_quote = 0;
	s_quote = 0;
	while (var->cmd[++i])
	{
		if (var->cmd[i] == '"' && s_quote == FALSE)
		{
			check_d_quote(&d_quote);
			d_quote_count++;
		}
		if (var->cmd[i] == '\'' && d_quote == FALSE)
		{
			check_s_quote(&s_quote);
			s_quote_count++;
		}
	}
	return (d_quote_count % 2 + s_quote_count % 2);
}

int	check_redirection_syntax(char **input, int i, char c)
{
	int		j;
	char	d;

	j = -1;
	if (c == '<')
		d = '>';
	else
		d = '<';
	while (input[i][++j] == c)
	{
		if (j == 2)
			return (syntax_error(input, i, j));
		else if (input[i][j + 1] == d)
			return (syntax_error(input, i, j));
		else if (input[i + 1] == NULL && input[i][j + 1] != c)
			return (syntax_error(input, i, j));
		else if (input[i + 1]
			&& (input[i + 1][0] == d || input[i + 1][0] == c))
			return (syntax_error(input, i + 1, 3));
	}
	return (0);
}

int	syntax_check(char **input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (check_redirection_syntax(input, i, '<') == -1)
			return (-1);
		if (check_redirection_syntax(input, i, '>') == -1)
			return (-1);
	}
	return (0);
}
