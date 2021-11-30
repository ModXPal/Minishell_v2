/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/30 18:34:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*trim_expand(char *str)
{
	int	len;
	int i;
	char *trim;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (str[i + 1] == ' ')
			{
				i++;
				if (len != 0 && str[i - 1] == 0)
					len++;
			}
		}
		if (str[i])
			len++;
	}
	trim = ft_calloc(sizeof(char), len + 1);
	if (trim == NULL)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (len != 0 && str[i - 1] == ' ')
			trim[len++] = ' ';
		trim[len++] = str[i];
	}
	return (trim);
}

char	*get_valid_envar(t_var *var, char *str, int i)
{
	t_envar	*tmp;
	int		j;
	int		k;

	tmp = var->envar;
	if (str[i] == '?')
		return (ft_itoa(EXIT_STATUS));
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
			if (str[k] == 0 || ((ft_isalnum(str[k]) == 0) && str[k] != '_'))
			{
				if (var->d_quote == FALSE)
					return (trim_expand(tmp->content));
				return (ft_strdup(tmp->content));
			}
		}
		tmp = tmp->next;
	}
	return (ft_strdup("\0"));
}

char	*ft_trim(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;
	int		k;
	char 	*envar;

	trim_str = (char *)ft_calloc(sizeof(char), (len + 1));
	printf("len = %d\n", len + 1);
	if (!trim_str)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (check_quotes(str, &j, var) == TRUE)
			continue ;
		if (str[j] == '$' && var->s_quote == FALSE)
		{
			k = 0;
			j++;
			envar = get_valid_envar(var, str, j);
			printf("envar = %s\n", envar);
			while (envar[k])
				trim_str[i++] = envar[k++];
			if (envar)
			{
				free(envar);
				envar = NULL;
			}
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	return (trim_str);
}

t_input	*get_input(t_var *var, char **split_input)
{
	t_input	*new;
	int 	args_len;

	new = malloc(sizeof(t_input));
	if (new == 0)
		return (0);
	args_len = split_len(split_input) + 1;
	new->args = (char **)ft_calloc(sizeof(char *),
			 (args_len/* + count_heredoc(split_input)*/));
	new->cmd = NULL;
	new->IN_FD = 0;
	new->OUT_FD = 0;
	new->heredoc = 0;
	printf("args len = %d\n", args_len);
	handle_input(var, new, split_input);
	/*
	if (handle_input(var, new, split_input) == 2)
	{
	 */
		if (args_len/*+ count_heredoc(split_input)*/ == 1)
		{
			printf("args len in if= %d\n", args_len);
			free(new->args);
			new->args = NULL;
			return (NULL);
		}
		/*
		else
			free_split (new->args);
		return (new);
	}
		 */
	//for (int l = 0; new->args[l]; l++)
	//	printf("args[%d] = %s\n", l, new->args[l]);
	return (new);
}

int	create_input_list(t_var *var, char *split_pipes)
{
	t_input	*new;
	char	**split_input;

	split_input = ft_split_quotes(split_pipes, ' ');
	if (syntax_check(split_input) == -1)
	{
		free_split (split_input);
		return (-1);
	}
	new = get_input(var, split_input);
	if (new)
		input_add_back(&var->input, new);
	free_split(split_input);
	return (0);
}

int	get_arguments(t_var *var)
{
	char	**split_pipes;
	int		i;

	i = -1;
	var->cmd_nb = count_pipes(var);
	if (var->cmd[0] == 0)
		return (-1);
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		EXIT_STATUS = 1;
		return (-1);
	}
	if (check_pipes(var) == -1)
		return (-1);
	split_pipes = ft_split_pipes(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		if (create_input_list(var, split_pipes[i]) == -1)
		{
			free_split(split_pipes);
			return (-1);
		}
	}
	free_split(split_pipes);
	return (0);
}
