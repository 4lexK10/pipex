/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:26:42 by akloster          #+#    #+#             */
/*   Updated: 2024/06/19 18:29:47 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd_child(char **argv, int *fds, char *path)
{
	char	**arg;
	char	**envp;
	char	*temp;

	if (child_files(fds, path) == -1)
		return (-1);
	envp = (char **)malloc(1 * sizeof(char *));
	arg = (char **)malloc(2 * sizeof(char *));
	if (!envp || !arg)
	{
		free_ptr_array(&arg);
		free_ptr_array(&envp);
		return (ft_error("malloc", HAS_ERRNO));
	}
	envp[0] = NULL;
	arg[0] = ft_strtrim(argv[3], " ");
	arg[1] = NULL;
	if (!(*arg))
	{
		free_ptr_array(&envp);
		free_ptr_array(&arg);
		return (ft_error("malloc", HAS_ERRNO));
	}
	temp = ft_strdup(arg[0]);
	free(arg[0]);
	arg[0] = ft_strjoin("/bin/", temp);
	free(temp);
	if (execve(arg[0], arg, envp) == -1)
		return (ft_error("execve", HAS_ERRNO));
	return (0);
}

int	exec_cmd_parent(char **argv, int *fds, char *path)
{
	char	**arg;
	char	**envp;
	char	*temp;

	envp = (char **)malloc(1 * sizeof(char *));
	arg = (char **)malloc(2 * sizeof(char *));
	if (!envp || !arg)
	{
		free_ptr_array(&arg);
		free_ptr_array(&envp);
		return (ft_error("malloc", HAS_ERRNO));
	}
	envp[0] = NULL;
	arg[0] = ft_strtrim(argv[2], " ");
	arg[1] = NULL;
	/*  	for (int i = 0; arg[i] != NULL; ++i)
		printf("|%s|\n", arg[i]); */
	if (!(*arg))
	{

		free_ptr_array(&arg);
		free_ptr_array(&envp);
		return (ft_error("malloc", HAS_ERRNO));
	}
	temp = ft_strdup(arg[0]);
	free(arg[0]);
	arg[0] = ft_strjoin("/bin/", temp);
	free(temp);
    	printf("arg[0]: |%s|\n", arg[0]);
	if (parent_files(fds, path) == -1)
		return (-1);
	if (execve(arg[0], arg, envp) == -1)
		return (ft_error("execve", HAS_ERRNO));
	return (0);
}
