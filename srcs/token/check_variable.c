#include "../../includes/minishell.h"

int	check_status(char **str)
{
	char	*tpm;
	int		i;

	i = 0;
	if (ft_strlen(*str) == 2)
	{
		if (ft_strncmp(*str, "$?", 2) == 0)
		{
			tpm = ft_itoa(get_sig_code());
			free(*str);
			*str = NULL;
			*str = ft_strdup(tpm);
			free(tpm);
			return (1);
		}
	}
	return (0);
}

int	search_variable(char **str)
{
	int		i;
	size_t	j;
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
	if (j != ft_strlen(tpm))
		*str = ft_strdup("");
	else
		*str = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	free(tpm);
	return (1);
}