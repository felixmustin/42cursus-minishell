#include "../includes/minishell.h"

char *parse_cwd(char *cwd)
{
    char *last_cwd;
    char *cut_cwd;
    int i;
    int j;

    i = ft_strlen(cwd);
    j = i;
    while(cwd[i] != '/')
        i--;
    cut_cwd = malloc(sizeof(char) * (j - i) + 1);
    if (!cut_cwd)
        return (NULL);
    j = 0;
    while (cwd[++i])
        cut_cwd[j++] = cwd[i];
    cut_cwd[j++] = ' ';
    cut_cwd[j] = 0;
    last_cwd = ft_strjoin("\U0001F449 ", cut_cwd);
    free(cut_cwd);
    return (last_cwd);   
}

char *new_prompt(void)
{
    char *cwd;
    char *last_cwd;

    cwd = getcwd(NULL, 0);
    last_cwd = parse_cwd(cwd);
    free(cwd);
    return (last_cwd);
}