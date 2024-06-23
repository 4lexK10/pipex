/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:26:42 by akloster          #+#    #+#             */
/*   Updated: 2024/06/21 18:39:00 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd_child(char **argv, int *fds, char *path, char **envp)
{
	char	**arg;
	char	**check;
	char	**all_path;
	char	*bin_with_path;

/* 	write(1, "child\n", 6); */
	if (child_files(fds, path) == -1)
		return (-1);
	arg = ft_split(argv[3], ' ');
	if (!arg)
	{
		return (ft_error("malloc", HAS_ERRNO));
	}
	all_path = get_all_path(envp);
	check = find_path(arg, all_path);
	if (!check)
		return (-1);
	/*  	while (**check != '\0')
	{
		write(2, &(**check), 1);
		++(*check);
	}
	write(2, "\n", 1); */
	bin_with_path = ft_strjoin(complete_path(check[0]), arg[0]);
	if (execve(bin_with_path, arg, envp) == -1)
		return (ft_error("execve", HAS_ERRNO));
	return (ft_error("execution error", NO_ERRNO));
}

int	exec_cmd_parent(char **argv, int *fds, char *path, char **envp)
{
	char	**arg;
	char	**check;
	char	**all_path;
	char	*bin_with_path;

/* 	write(1, "parent\n", 7); */
	arg = ft_split(argv[2], ' ');
	if (!arg)
	{
		return (ft_error("malloc", HAS_ERRNO));
	}
	if (parent_files(fds, path) == -1)
		return (-1);
	all_path = get_all_path(envp);
	check = find_path(arg, all_path);
	if (!check)
		return (-1);
	/*  	while (**check != '\0')
	{
		write(2, &(**check), 1);
		++(*check);
	}
	write(2, "\n", 1); */
	bin_with_path = ft_strjoin(complete_path(check[0]), arg[0]);
	if (execve(bin_with_path, arg, envp) == -1)
		return (ft_error("execve", HAS_ERRNO));
	
	return (ft_error("execution error", NO_ERRNO));
}

