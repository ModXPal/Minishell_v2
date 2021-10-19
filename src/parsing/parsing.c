/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/19 22:48:58 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_input	*get_input(t_var *var, char **split_input)
{
	int		i;
	int		len;
	char		*content;
	t_input		*new;

	i = -1;
	new = malloc(sizeof(t_input));
	new->args = (char **)malloc(sizeof(char *) * (split_len(split_input) + 1));
	if (new->args == FAIL)
		return (0);
	while (split_input[++i])
	{
		var->s_quote = 0;
		var->d_quote = 0;
		len = get_string_len(split_input[i], var);
		var->s_quote = 0;
		var->d_quote = 0;
		content = ft_trim(var, split_input[i], len);
		if (i == 0)
			new->cmd = content;
		new->args[i] = content;
	}
	new->args[i] = NULL;
	new->next = NULL;
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
	t_input *last;

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
	t_input		*new;

	i = -1;
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		return (0);
	}
	split_pipes = ft_split(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		split_input = ft_split_quotes(split_pipes[i], ' ');
		new = get_input(var, split_input);
		input_add_back(&var->input, new);
		free_split(split_input);
	}
	free_split(split_pipes);
	return (1);
}
