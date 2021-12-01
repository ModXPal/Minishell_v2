#include "builtin.h"

int	ft_pwd(t_var *var)
{
	t_envar	*tmp;
	char	*str;
	char	*test;

	tmp = var->envar;
	str = NULL;
	str = ft_envar_find_content(tmp, "PWD");
	test = getcwd(NULL, 0);
	if (test == NULL)
	{
		EXIT_STATUS = 1;
		perror("pwd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return (EXIT_STATUS);
	}
	printf("%s\n", test);
	if (test != 0)
		free (test);
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
