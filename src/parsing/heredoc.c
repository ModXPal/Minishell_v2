#include "parsing.h"

char	*delete_last_line(char *str)
{
	int		i;
	char	*final_str;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 2;
	while (str[i - 1] != '\n')
		i--;
	final_str = malloc(sizeof(char) * i);
	if (final_str == 0)
		return (NULL);
	final_str[i] = 0;
	while (--i >= 0)
		final_str[i] = str[i];
	free (str);
	return (final_str);
}

char	*trim_heredoc(char *str, int len, t_var *var)
{
	char	*trim_str;
	int		i;
	int		j;
	int		k;

	trim_str = ft_calloc(sizeof(char), (len + 1));
	if (!trim_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		k = 0;
		if (str[j] == '$' && ft_isalnum(str[j + 1]))
		{
			j++;
			while (get_valid_envar(var, str, j)[k])
				trim_str[i++] = get_valid_envar(var, str, j)[k++];
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	free (str);
	return (trim_str);
}

void	get_next_line(char **line, int *i)
{
	char	buff[2];
	int		ret;

	if (*i != 0)
		*line = ft_strjoin(*line, "\n");
	*i = 0;
	ret = 1;
	buff[0] = 0;
	write(STDOUT_FILENO, "> ", 2);
	while (ret > 0 && buff[0] != '\n')
	{
		ret = read(STDIN_FILENO, buff, 1);
		buff[1] = 0;
		if (buff[0] != '\n')
			*line = ft_strjoin(*line, buff);
		(*i)++;
	}
	(*i)--;
}

int	here_doc(t_input *input, char *delimiter, t_var *var)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	line = ft_strdup("");
	input->IN_FD = 0;
	while (ft_strcmp(&line[ft_strlen(line) - i], delimiter) == 0)
		get_next_line(&line, &i);
	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	line = delete_last_line(line);
	if (input->heredoc)
		free(input->heredoc);
	input->heredoc = trim_heredoc(line, get_heredoc_len(line, var), var);
	return (0);
}
