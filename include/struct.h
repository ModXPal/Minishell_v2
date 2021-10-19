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
	struct s_list		*list;
	struct s_envar		*envar;
	struct s_envar		*export;
	struct s_pipes		*pipes;
	struct s_cd			*cd;
}		t_var;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_var *);
}		t_builtin;

#endif
