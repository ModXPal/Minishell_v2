/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:42:24 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/01 15:03:52 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>

int EXIT_STATUS;

typedef struct s_echo{
	struct s_list	*echo_list;
	char			*echo;
	int				simple_quote;
	int				double_double;
	int				dash_n;
	int				dollar;
}	t_echo;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_input{
	char	*cmd;
	char	**args;
	int	**redir_nb;
	int			IN_FD;
	int			OUT_FD;
	struct s_input *next;
}		t_input;

typedef struct s_pvar{
	int				cmd_nb;
	pid_t			*pids;
	char			*cmd;
	char			**path;
}	t_pvar;

typedef struct s_cd{
	// char			*HOME; // on va surement pas gerer le unset donc a supprimer
	char			*cdpath;
	int				exit_cd;
}	t_cd;

typedef struct s_envar{
	char			*name;
	char			*content;
	struct s_envar	*next;
}		t_envar;

typedef struct s_var{
	char			**env;
	char			*cmd;
	char			*variable;
	int				ac;
	int				exit_status;
	int				s_quote;
	int				d_quote;
	char			interruption;
	t_list			*list;
	t_input			*input;
	t_envar			*envar;
	t_envar			*export;
	//t_pipes		*pipes;
	t_cd			*cd;
}		t_var;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_var *);
}		t_builtin;

#endif
