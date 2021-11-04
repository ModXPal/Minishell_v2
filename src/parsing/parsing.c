/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/31 18:06:48 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_redirection(char	**input)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j] == '<' || input[i][j] == '>')
		{
			if (input[i][j + 1] == 0)
				count++;
		}
	}
	return (count);
}

char	*get_valid_envar(t_var *var, char *str, int i)
{
	t_envar	*tmp;
	int		j;
	int		k;

	tmp = var->envar;
	while (tmp)
	{
		j = 0;
		k = i;
		while (tmp->name[j] && str[k])
		{
			if (ft_charcmp((tmp->name)[j], str[k]) == FAIL)
				break ;
			j++;
			k++;
			if ((ft_isalnum(str[k]) == 0) || str[k] == 0)
				return (tmp->content);
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*ft_trim(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;
	int		k;

	trim_str = (char *)malloc(sizeof(char) * (len + 1));
	j = 0;
	i = 0;
	while (i < len)
	{
		k = 0;
		if (check_quotes(str, &j, var) == TRUE)
			continue ;
		if (str[j] == '$' && var->s_quote == FALSE && ft_isalnum(str[j + 1]))
		{
			j++;
			while (get_valid_envar(var, str, j)[k])
				trim_str[i++] = get_valid_envar(var, str, j)[k++];
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	trim_str[i] = 0;
	return (trim_str);
}

int	count_pipes(t_var *var)
{
	int	i;
	int	pipe_count;

	i = -1;
	pipe_count = 1;
	while (var->cmd[++i])
	{
		if (var->cmd[i] == '|')
			pipe_count++;
	}
	return (pipe_count);
}

int	is_option(char *str)
{
	if (str[0] == '-')
		return (1);
	return (0);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
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
	else if (input[i][0] == '<' && input[i][1] == '>')
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][1], ft_strlen(&input[i][1]));
		write (2, "'\n", 2);
	}
	else if (input[i][0] == '>' && input[i][1] == '<')
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][1], ft_strlen(&input[i][1]));
		write (2, "'\n", 2);
	}
	else
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, "newline", 7);
		write (2, "'\n", 2);
	}
	return (-1);
}

int	syntax_check(char **input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j] == '<')
		{
			if (j == 2)
				return (syntax_error(input, i, j));
			else if (input[i][j + 1] == '>')
				return (syntax_error(input, i, j));
			else if (input[i + 1] == NULL && input[i][j + 1] != '<')
				return (syntax_error(input, i, j));
			else if (input[i + 1] && input[i + 1][0] == '>')
				return (syntax_error(input, i + 1, 3));
		}
		j = -1;
		while (input[i][++j] == '>')
		{
			if (j == 2)
				return (syntax_error(input, i, j));
			else if (input[i][j + 1] == '<')
				return (syntax_error(input, i, j));
			else if (input[i + 1] == NULL && input[i][j + 1] != '>')
				return (syntax_error(input, i, j));
			else if (input[i + 1] && input[i + 1][0] == '<')
				return (syntax_error(input, i + 1, 3));
		}
	}
	return (0);
}

int	open_files(t_input *input, char *file, int redir)
{
	if (redir == STDIN)
	{
		input->in_fd = open(file, O_RDONLY);
	}
	else if (redir == STDOUT)
	{
		input->out_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (redir == STDOUT_APPEND)
	{
		input->out_fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	return (0);
}

t_input	*get_input(t_var *var, char **split_input)
{
	int		i;
	int		j;
	int		len;
	char	*content;
	t_input	*new;

	i = -1;
	new = malloc(sizeof(t_input));
	new->args = (char **)malloc(sizeof(char *) * (split_len(split_input) + 1));
	new->cmd = NULL;
	if (new->args == FAIL)
		return (0);
	new->redir_nb = malloc(sizeof(int *) * count_redirection(split_input));
	new->in_fd = 0;
	new->out_fd = 0;
	while (++i < count_redirection(split_input))
		new->redir_nb = malloc(sizeof(int) * count_redirection(split_input));
	i = -1;
	j = 0;
	while (split_input[++i])
	{
		var->s_quote = 0;
		var->d_quote = 0;
		len = get_string_len(split_input[i], var);
		var->s_quote = 0;
		var->d_quote = 0;
		content = ft_trim(var, split_input[i], len);
		if (ft_strcmp(split_input[i], "<") == TRUE)
		{
			i++;
			open_files(new, ft_trim(var, split_input[i],
					get_string_len(split_input[i], var)), STDIN);
			continue ;
		}
		else if (ft_strcmp(split_input[i], ">") == TRUE)
		{
			i++;
			open_files(new, ft_trim(var, split_input[i],
					get_string_len(split_input[i], var)), STDOUT);
			continue ;
		}
		else if (ft_strcmp(split_input[i], ">>") == TRUE)
		{
			i++;
			open_files(new, ft_trim(var, split_input[i],
					get_string_len(split_input[i], var)), STDOUT_APPEND);
			continue ;
		}
		else if (i == 0 || ((new->in_fd > 0
				|| new->out_fd > 0) && new->cmd == NULL))
			new->cmd = content;
		//printf("content = %s\n", content);
		new->args[j++] = content;
	}
	new->args[j] = NULL;
	new->next = NULL;
	//printf("in fd = %d\n", var->in_fd);
	//printf("out fd = %d\n", var->out_fd);
	return (new);
}

t_input	*ft_inptlast(t_input *input)
{
	if (!input)
		return (NULL);
	while (input)
	{
		if (input->next == NULL)
			return (input);
		input = input->next;
	}
	return (NULL);
}

void	input_add_back(t_input **ainpt, t_input *new)
{
	t_input	*last;

	if (!ainpt || !new)
		return ;
	if (*ainpt)
	{
		last = ft_inptlast(*ainpt);
		last->next = new;
	}
	else
		*ainpt = new;
}

int	get_arguments(t_var *var)
{
	char	**split_input;
	char	**split_pipes;
	int		i;
	t_input	*new;

	i = -1;
	if (var->cmd[0] == 0)
		return (-1);
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		return (-1);
	}
	split_pipes = ft_split(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		split_input = ft_split_quotes(split_pipes[i], ' ');
		if (syntax_check(split_input) == -1)
			return (-1);
		new = get_input(var, split_input);
		input_add_back(&var->input, new);
		free_split(split_input);
	}
	free_split(split_pipes);
	return (1);
}
