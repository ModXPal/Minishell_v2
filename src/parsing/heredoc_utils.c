/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:08:33 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 14:50:05 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	here_doc_ctrl_d_equal_one(t_var *var, t_input *input,
				char *line, char *delimiter)
{
	printf("\n");
	dup2(var->save_stdin, STDIN_FILENO);
	if (input->heredoc)
		free(input->heredoc);
	input->heredoc = trim_heredoc(line, get_heredoc_len(line, var), var);
	free (delimiter);
}

void	init_variable_here_doc(t_var *var, t_input *input)
{
	g_exit_status = 300;
	var->here_doc_ctrl_d = 0;
	input->in_fd = 0;
}

int	boucle_get_next_line(char **line, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (*i != 0)
	{
		tmp = *line;
		*line = ft_strjoin(*line, "\n");
		free (tmp);
	}
	return (0);
}
