#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>

extern int	g_exit_status;

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
	char			*cmd;
	char			*heredoc;
	char			**args;
	int				in_fd;
	int				out_fd;
	struct s_input	*next;
}		t_input;

typedef struct s_cd{
	char			*cdpath;
	int				exit_cd;
	int				cdpath_exist;
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
	char			*export_name;
	char			*export_content;
	char			*env_name;
	char			*env_content;
	char			*trim_expand;
	char			*exit_code;
	int				reassigned;
	int				ac;
	int				equal_env;
	int				exit_status;
	int				s_quote;
	int				d_quote;
	int				cmd_nb;
	char			interruption;
	int				error;
	int				save_stdin;
	int				save_stdout;
	int				pwd_exist;
	int				here_doc_ctrl_d;
	int				oldpwd_exist;
	int 			expand;
	int 			abort_heredoc;
	int 			split_end;
	t_list			*list;
	t_input			*input;
	t_input			*to_free;
	t_envar			*envar;
	t_envar			*export;
	t_cd			*cd;
	void			*pvar;
	void			*builtin;
}		t_var;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_var *);
}		t_builtin;

typedef struct s_pvar{
	int				cmd_nb;
	int				ret;
	pid_t			*pids;
	char			*cmd;
	char			**path;
	t_builtin		*builtin;
}	t_pvar;

#endif
