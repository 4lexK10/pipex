#include "pipex.h"


char	*complete_path(char *path)
{
	char	*temp;
	char	*new_path;

	temp = ft_strdup(path);
	new_path = ft_strjoin(temp, "/");	
	my_free(&temp, 0);
	if (!new_path)
		return (NULL);
	return (new_path);
}

static char	**give_path(char **envp, int i)
{
	char	**path;

	path = (char **)malloc(2 * sizeof(char *));
	if (!path)
	{
		ft_error("malloc", HAS_ERRNO);
		return (NULL);
	}
	path[0] = ft_strdup(envp[i]);
	if (!(path[0]))
	{
		ft_error("malloc", HAS_ERRNO);
		return (NULL);
	}
	path[1] = NULL;
	return (path);
}

char **get_all_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 6))
		++i;
	if (!envp[i])
	{
		ft_error("error: environment variable missing", NO_ERRNO);
		return (NULL);
	}
	path = ft_split(&envp[i][5], ':');
	/* 	for (int i = 0; path[i] != NULL; ++i) 
		printf("|%s|\n", path[i]); */
	if (!path)
	{
		ft_error("malloc", HAS_ERRNO);
		return (NULL); 
	}
	return (path);
}

char **find_path(char **bin, char **envp)
{
	char	*test;
	char	*temp;
	int		i;
	int		nbr_paths;

	i = -1;
	nbr_paths = 0;
	while (envp[nbr_paths] != NULL)
		++nbr_paths;
	while (nbr_paths--)
	{
		temp = complete_path(envp[++i]);
		test = ft_strjoin(temp, bin[0]);
		if (!test)
		{
			ft_error("malloc", HAS_ERRNO);
			return (NULL);
		}
		if (access(test, F_OK | X_OK) != -1)
			return (give_path(envp,	i));
/* 		while (*test != '\0')
		{
			write(2, &(*test), 1);
			++test;
		}
		write(2, "\n", 1); */
	}
	ft_error("binary not found", NO_ERRNO);
	return (NULL);
}


