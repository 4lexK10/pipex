/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:26:42 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 13:31:56 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_arg(char *argv)
{
	char	**arg;

	arg = NULL;
	if (ft_strrchr(argv, 39))
		arg = special_case(ft_split(argv, 39));
	else
		arg = ft_split(argv, ' ');
	if (!arg)
	{
		ft_error("malloc", HAS_ERRNO);
		return (NULL);
	}
	return (arg);
}

static char	*get_bin_path(char *path, char *bin)
{
	char	*path_bin;
	char	*temp;

	temp = complete_path(path);
	path_bin = ft_strjoin(temp, bin);
	my_free(&temp, 0);
	return (path_bin);
}

static char	**absolute_path_check(char *argv)
{
	char	**abs_bin;
	char	**res;

	abs_bin = ft_split(argv, ' ');
	if (!abs_bin)
		return (error_return_null("malloc"));
	if (access(abs_bin[0], F_OK | X_OK) == -1)
	{
		free_ptr_array(&abs_bin);
		return (NULL);
	}
	res = get_full_arg(abs_bin);
	free_ptr_array(&abs_bin);
	if (!res)
		return (error_return_null("malloc"));
	return (res);
}

int	exec_cmd(char *argv, char **envp)
{
	char	**arg;
	char	**check;
	char	**all_path;
	char	*bin;

	arg = absolute_path_check(argv);
	if (arg)
	{
		if (execve(arg[0], &arg[1], envp) == -1 && free_return(&arg, 1))
			return (ft_error("execve", HAS_ERRNO));
	}
	arg = get_arg(argv);
	if (!arg)
		return (-1);
	all_path = get_all_path(envp);
	check = find_path(arg, all_path);
	free_ptr_array(&all_path);
	if (!check && exec_free_all(&arg, NULL, NULL))
		return (-1);
	bin = get_bin_path(check[0], arg[0]);
	if (!bin && exec_free_all(&arg, &check, &bin))
		return (ft_error("malloc", HAS_ERRNO));
	if (execve(bin, arg, envp) == -1 && exec_free_all(&arg, &check, &bin))
		return (ft_error("execve", HAS_ERRNO));
	return (0);
}
