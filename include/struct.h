#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_echo{
	struct s_list	*echo_list;
	char			*echo;
	int				simple_quote;
	int				double_double;
	int				dash_n;
	int				dollar;
}	t_echo;

enum Operator{
	PIPE = 1,
	REDIRECT = 2,
	APPEND = 3
};

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_input{
	char	*cmd;
	char	**args;
	int	delimiter;
	int	opt_nb;
	int	arg_nb;
	struct s_input *next;
}		t_input;

typedef	struct s_pipes{
	int				size_cmd_pipes;
	int				**tab_pipes;
	int				i;
	int				fd[2];
} t_pipes;

typedef	struct s_cd{
	char			*HOME;
	char			*cdpath;
} t_cd;

typedef struct s_envar{
	char			*name;
	char			*content;
	struct s_envar	*next;
}		t_envar;

typedef struct s_var{
	char				**env;
	char				*cmd;
	char				*variable;
	int					ac;
	int					s_quote;
	int					d_quote;
	t_list		*list;
	t_input		*input;
	t_envar		*envar;
	t_envar		*export;
	t_pipes		*pipes;
	t_cd			*cd;
}		t_var;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_var *);
}		t_builtin;

#endif
