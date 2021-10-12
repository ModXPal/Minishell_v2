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
	int			s_quote;
	int			d_quote;
	struct s_list	*list;
	struct s_envar	*envar;
	struct s_envar	*export;
}		t_var;

typedef struct s_builtin{
	char	*cmd;
	int		(*func)(t_var *);
}		t_builtin;

#endif
