/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:31:43 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/06 18:06:46 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define STDIN 0
# define STDOUT 1
# define STDOUT_APPEND 2
# define HERE_DOC 3

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "struct.h"

char	*get_valid_envar(t_var *var, char *str, int i);
char	*ft_trim(t_var *var, char *str, int len);
char	*ft_trim_delimiter(t_var *var, char *str, int len);
char	*get_var_name(char **env, int i);
char	*get_var_content(char **env, int i);
void	check_s_quote(int *s_quote);
void	check_d_quote(int *d_quote);
void	get_envar_len(int *j, int *i, t_var *var, char *str);
void	skip_alnum(char *str, int *j);
void	free_split(char **split_str);
void	free_list(t_var *var);
void	get_env_var(t_var *var, t_envar **envar);
int		get_string_len(char *str, t_var *var);
int		is_valid_dollar(char *str, int i);
int		check_quotes(char *str, int *j, t_var *var);
int		get_arguments(t_var *var);
int		check_unmatched_quotes(t_var *var);
int		count_pipes(t_var *var);
int		ft_strcmp(const char *s1, const char *s2);
void	init_builtin(t_builtin *builtin);
void	init_var(t_var *var, char **env, int ac);
char	*get_valid_envar(t_var *var, char *str, int i);
int		get_heredoc_len(char *str, t_var *var);
int		syntax_error(char **input, int i, int j);
int		pipe_error(void);
void	permission_denied(char *file);
void	missing_file(char *file);
void	assign_envar(char *envar, char *trim_str, int *i);
int		syntax_check(char **input);
int		check_pipes(t_var *var);
int		here_doc(t_input *input, char *delimiter, t_var *var);
int		handle_redir(t_var *var, t_input *input, char **split_input, int *i);
int		count_heredoc(char **split_input);
int		split_len(char **split);
int		count_pipes(t_var *var);
int		handle_input(t_var *var, t_input *new, char **split_input);
int		get_delimiter_len(char *str, t_var *var);
void	assign_envar(char *envar, char *trim_str, int *i);
char	*get_valid_envar(t_var *var, char *str, int i);
void	set_var(int *j, int *k, int i);
char	*trim_expand(char *str);
char	*trim_heredoc(char *str, int len, t_var *var);
int		expand_len(char *str);
int		boucle_get_next_line(char **line, int *i);
char	*ft_trim(t_var *var, char *str, int len);
void	here_doc_ctrl_d_equal_one(t_var *var, t_input *input,
			char *line, char *delimiter);
void	init_variable_here_doc(t_var *var, t_input *input);

#endif
