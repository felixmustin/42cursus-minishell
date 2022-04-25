#include "../../includes/minishell.h"

char	*split_to_str(char **split)
{
	char	*str;
	char	*tpm;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (split[i] != NULL)
	{
		tpm = ft_strdup(str);
		free(str);
		str = NULL;
		str = ft_strjoin(tpm, split[i]);
		free(tpm);
		tpm = NULL;
		i++;
	}
	return (str);
}

int	delete_double_quotes(t_token *token)
{
	char	**tpm;

	if (ft_strlen(token->content) == 2)
	{
		token->type = undesirable;
		return (0);
	}
	tpm = ft_split(token->content, 34);
	free(token->content);
	token->content = NULL;
	token->content = split_to_str(tpm);
	return (0);
}

int	delete_single_quotes(t_token *token)
{
	char	**tpm;

	if (ft_strlen(token->content) == 2)
	{
		token->type = undesirable;
		return (0);
	}
	tpm = ft_split(token->content, 39);
	free(token->content);
	token->content = NULL;
	token->content = split_to_str(tpm);
	return (0);
}

int	delete_quotes(t_lists **lst)
{
	t_lists	*tpm;

	tpm = *lst;
	while (*lst)
	{
		if ((*lst)->token->type == double_quote)
			delete_double_quotes((*lst)->token);
		if ((*lst)->token->type == single_quote)
			delete_single_quotes((*lst)->token);
		*lst = (*lst)->next;
	}
	*lst = tpm;
	return (0);
}
