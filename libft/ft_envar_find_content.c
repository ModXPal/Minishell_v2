#include "libft.h"

char	*ft_envar_find_content(t_envar *tmp, char *str)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			str = tmp->content;
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
