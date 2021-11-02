/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/02 17:58:46 by rcollas          ###   ########.fr       */
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

char	*delete_last_line(char *str)
{
	int	i;
	char	*final_str;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 2;
	while (str[i - 1] != '\n')
		i--;
	final_str = malloc(sizeof(char) * i);
	final_str[i] = 0;
	while (--i >= 0)
		final_str[i] = str[i];
	return (final_str);
}

int	here_doc(t_input *input, char *delimiter)
{
	char    *line;
	char	buff[2];
	int		ret;
	int		i;
	int		j;

	line = ft_strdup("");
	j = 0;
	i = 0;
	while (ft_strcmp(&line[ft_strlen(line) - i], delimiter) == 0)
	{
		if (i != 0)
			line = ft_strjoin(line, "\n");
		i = 0;
		ret = 1;
		buff[0] = 0;
		write(STDOUT_FILENO, "> ", 2);
		while (ret > 0 && buff[0] != '\n')
		{
			ret = read(STDIN_FILENO, buff, 1);
			buff[1] = 0;
			if (buff[0] != '\n')
				line = ft_strjoin(line, buff);
			i++;
		}
		i--;
	}
	line = ft_strjoin(line, "\n");
	line = delete_last_line(line);
	//printf("%s\n", line);
	input->heredoc = line;
	return (0);
}

int	open_files(t_input *input, char *file, int redir)
{
	if (redir == STDIN)
	{
		input->IN_FD = open(file, O_RDONLY);
	}
	else if (redir == STDOUT)
	{
		input->OUT_FD = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (redir == STDOUT_APPEND)
	{
		input->OUT_FD = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (redir == HERE_DOC)
	{
		here_doc(input, file);
		input->IN_FD = 0;
	}
	return (0);
}

int	handle_redir(t_var *var, t_input *input, char **split_input, int *i)
{
	int	len;

	len = get_string_len(split_input[(*i) + 1], var);
	if (ft_strcmp(split_input[*i], "<") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDIN);
		if (input->IN_FD > 0)
			return (0);
	}
	else if (ft_strcmp(split_input[*i], "<<") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), HERE_DOC);
		return (0);
	}
	else if (ft_strcmp(split_input[*i], ">") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDOUT);
		if (input->OUT_FD > 0)
			return (0);
	}
	else if (ft_strcmp(split_input[*i], ">>") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDOUT_APPEND);
		if (input->OUT_FD > 0)
			return (0);
	}
	return (-1);
}

void	handle_input(t_var *var, t_input *new, char **split_input)
{
	int	i;
	int	j;
	int	len;
	char	*content;

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
		if (handle_redir(var, new, split_input, &i) == 0)
			continue ;
		else if (i == 0 || ((new->IN_FD > 0 || new->OUT_FD > 0 || new->heredoc) && new->cmd == NULL))
			new->cmd = content;
		//printf("content = %s\n", content);
		new->args[j++] = content;
	}
	new->args[j] = NULL;
	new->next = NULL;
}

int	count_heredoc(char **split_input)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (split_input[++i])
	{
		if (ft_strcmp(split_input[i], "<<") == TRUE)
			count++;
	}
	return (count);
}

t_input	*get_input(t_var *var, char **split_input)
{
	int		i;
	int		j;
	t_input	*new;

	i = -1;
	new = malloc(sizeof(t_input));
	if (new == 0)
		return (0);
	new->args = (char **)malloc(sizeof(char *) * (split_len(split_input) + count_heredoc(split_input) + 1));
	if (new->args == FAIL)
		return (0);
	new->cmd = NULL;
	new->IN_FD = 0;
	new->OUT_FD = 0;
	new->heredoc = 0;
	i = -1;
	j = 0;
	handle_input(var, new, split_input);
		//printf("in fd = %d\n", var->IN_FD);
	//printf("out fd = %d\n", var->OUT_FD);
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
