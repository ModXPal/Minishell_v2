/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:04:47 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 18:04:48 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define EXPORT 127
# define ENV 100

# include "struct.h"
# include "../libft/libft.h"

int		is_dash_n(char *str);
int		ft_echo(t_var *var);
int		ft_env(t_var *var);
int		ft_exit(t_var *var);
int		ft_pwd(t_var *var);
int		ft_unset(t_var *var);
int		ft_cd(t_var *var);
int		ft_export(t_var *var);
int		ft_unset(t_var *var);
int		ft_multipipes(t_var *var, t_builtin *builtin);
int		cmd_export_alone(t_var *var);
char	*export_name_equal_search(char *str, int *i, int *equal, char *name);
char	*export_content_search(int *i, char *str, char *content);
char	*ft_export_new_pwd(t_var *var, char *str);
void	ft_export_old_pwd(t_var *var, char *str, char *str2);
int		swap_pwd_old_pwd(t_var *var);
char	*ft_env_new_pwd(t_var *var, char *str);
int		errors_chdir_handling(int dir, t_var *var);
void	ft_env_old_pwd(t_var *var, char *str, char *str2);
int		unset_export_error_handling(t_var *var, char *content);
int		parsing_child(t_var *var);
void	parsing_parent(t_var *var, int parent);
char	*cd_str_and_path_not_set(t_var *var);
int		get_home_unset_cd(t_var *var);
int		cd_content_equal_tild_dash(t_var *var);
int		cd_content_equal_zero(t_var *var);
int		cd_dash_equal_one(t_var *var);
int		unset_error_export_message(t_var *var, char *content);
int		check_cdpath_exists(t_var *var);
int		cd_application(t_var *var);
int		cd_dash_tild(t_var *var);
int		swap_pwd_old_pwd_and_errors(t_var *var, char *str, int dir);
int		cd_cdpath_application(t_var *var);
int		split_len(char **split);
char	*cd_str_and_path_not_set(t_var *var);
int		swap_current_pwd(t_var *var, char *str2, char *content);
void	free_list(t_var *var);
void	free_split(char **split_str);
void	free_envar(t_envar *envar);
void	free_input(t_var *var);
void	handle_sigusr1(int signum);
char	*ft_env_new_pwd_2(t_var *var, t_envar *tmp, char *str2, char *str);
int		cmd_export_insert(t_var *var, char *name, char *content);
int		export_name_len(t_var *var, char *str);
int		is_builtin(char *line, t_builtin *builtin);
void	handle_sigusr2(int signum);
int		cd_too_many_arguments(t_var *var);
void	cd_error_message_too_many_arguments(t_var *var);
int		ft_init_shlvl(t_var *var);
int		export_error_handling(t_var *var, char *content);
int		export_name_content(t_var *var, char *args);
int		export_env_reassigned_check(t_var *var, char *name,
			char *content);
int		export_export_reassigned_check(t_var *var, char *name,
			char *content, int export_already_exist);
int		export_env_insert(t_var *var, char *name, char *content);
int		ft_dup(t_var *var, int pipe_fd[2]);
int		dup_heredoc(t_var *var, int pipe_fd[2]);
int		dup_fd(t_var *var);
char	*env_name_init(t_var *var, char *args);
char	*env_content_init(t_var *var, char *args, int j);
int		name_already_exist(t_var *var, char *args, int i);
void	free_cd_path(t_var *var);
void	free_input_list(t_input *input);
void	ft_free(void *to_free);
void	free_with_pvar(t_var *var, t_pvar *pvar);
int		swap_pwd_with_args(t_var *var, t_envar *tmp, char *current_path);
int		check_if_pwd_exist(t_var *var);
int		cd_swap_with_no_args(t_var *var, t_envar *tmp, char *current_path);
int		error_chdir(t_var *var, int dir, char *str);
int		exit_non_numeric_arguments(t_var *var, int j, int i);
int		check_if_integers_first(t_var *var);
int		if_error_no_pwd_oldpwd(t_var *var);
int		cd_path_deploying(t_var *var);
void	init_signal(t_var *var);
void	ft_execve_2(t_var *var, int **pipe_fd, int ret, t_builtin *builtin);
void	signal_sigint_heredoc(void);

#endif
