#include "../../includes/minishell.h"

int	search_variable(char **str)
{
	int		i;
	int		j;
	char	*tpm;

	i = 0;
	tpm = ft_substr(*str, 1, ft_strlen(*str));
	while (env[i] && ft_strncmp(tpm, env[i], ft_strlen(tpm)) != 0)
		i++;
	if (!env[i])
	{
		free(*str);
		*str = ft_strdup("");
		return (0);
	}
	j = 0;
	while (env[i][j] != '=')
		j++;
	free(*str);
	*str = NULL;
	*str = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	return (1);
}