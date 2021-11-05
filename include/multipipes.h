/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:07:09 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/04 14:31:13 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPIPES_H
# define MULTIPIPES_H
# define FAIL 0
# define SUCCESS 1

# include "../libft/libft.h"
# include "struct.h"
# include "parsing.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

void	add_slash(t_pvar *pvar);
char	**get_binaries_path(t_var *var);
int		exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids);
int		close_pipes(t_pvar *pvar, int **pipefd);
int		check_access(t_pvar *pvar, int i);
int		cmd_not_found(t_var *var, t_pvar *pvar);
int		get_cmds(t_pvar *pvar, t_var *var);
int		first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i);
int		in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i);
int		last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i);
void	proceed_pipes(t_pvar *pvar, t_var *var, int **pipefd, int i);
int		exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids);
int		is_option(char *str);
int		count_pipes(t_var *var);
char	*ft_trim(t_var *var, char *str, int len);
int		split_len(char **split);
t_input	*get_input(t_var *var, char **split_input);
t_input	*ft_inptlast(t_input *input);
void	input_add_back(t_input **ainpt, t_input *new);
int		get_arguments(t_var *var);
int		is_builtin(char *line, t_builtin *builtin);

#endif
