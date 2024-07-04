/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:48:12 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 13:31:41 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*complete_path(char *path)
{
	char	*new_path;

	new_path = ft_strjoin(path, "/");
	if (!new_path)
		return (NULL);
	return (new_path);
}

static char	**give_path(char **envp, int i)
{
	char	**path;

	path = (char **)malloc(2 * sizeof(char *));
	if (!path)
		return (error_return_null("malloc"));
	path[0] = ft_strdup(envp[i]);
	if (!(path[0]))
	{
		free_ptr_array(&path);
		return (error_return_null("malloc"));
	}
	path[1] = NULL;
	return (path);
}

char	**get_all_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	if (!envp || !*envp)
		return (ft_split(
				"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':'));
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 6))
		++i;
	if (!envp[i])
	{
		ft_error("PATH unset", NO_ERRNO);
		return (NULL);
	}
	path = ft_split(&envp[i][5], ':');
	if (!path)
	{
		ft_error("malloc", HAS_ERRNO);
		return (NULL);
	}
	return (path);
}

char	**get_full_arg(char **argv)
{
	char	**full_args;
	int		i;

	i = 0;
	while (argv[i])
		++i;
	full_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!full_args)
		return (NULL);
	full_args[0] = ft_strdup(argv[0]);
	if (!full_args[0] && free_return(&full_args, 1))
		return (NULL);
	i = 1;
	while (argv[0][i] != '/' || argv[0][i] == 39 || argv[0][i] == '"')
		++i;
	full_args[1] = ft_strdup(&argv[0][i]);
	i = 0;
	while (argv[++i])
	{
		full_args[i + 1] = ft_strdup(argv[i]);
		if (!full_args[i + 1] && free_return(&full_args, 1))
			return (NULL);
	}
	full_args[i + 1] = NULL;
	return (full_args);
}

char	**find_path(char **bin, char **envp)
{
	char	*test;
	char	*temp;
	int		i;
	int		nbr_paths;

	if (!envp)
		return (NULL);
	i = -1;
	nbr_paths = 0;
	while (envp[nbr_paths] != NULL)
		++nbr_paths;
	while (nbr_paths--)
	{
		temp = complete_path(envp[++i]);
		test = ft_strjoin(temp, bin[0]);
		my_free(&temp, -1);
		if (!test)
			return (error_return_null("malloc"));
		if (access(test, F_OK | X_OK) != -1 && my_free(&test, 1))
			return (give_path(envp, i));
		my_free(&test, 0);
	}
	return (error_return_null("access"));
}
