/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:21:26 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 17:16:58 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**special_case(char **arg)
{
	char	**res;
	int		i;

	i = 0;
	if (!arg)
		return (NULL);
	while (arg[i])
		++i;
	res = (char **)malloc((i + 1) * sizeof(char *));
	if (!res && free_all(&arg, &res))
		return (NULL);
	res[0] = ft_strtrim(arg[0], " ");
	if (!res[0] && free_all(&arg, &res))
		return (NULL);
	i = 0;
	while (arg[++i])
	{
		res[i] = ft_strdup(arg[i]);
		if (!res[i] && free_all(&arg, &res))
			return (NULL);
	}
	res[i] = NULL;
	free_ptr_array(&arg);
	return (res);
}

static int	check_second_arg(char **argv, char **all_path)
{
	char	**arg;
	char	**temp;

	if (ft_strrchr(argv[3], 39))
		arg = special_case(ft_split(argv[3], 39));
	else
		arg = ft_split(argv[3], ' ');
	if (!arg)
		return (ft_error("malloc", HAS_ERRNO));
	if (!all_path && free_all(&arg, NULL))
		return (-1);
	temp = find_path(arg, all_path);
	if (!temp && free_all(&arg, &temp))
		return (-1);
	free_all(&arg, &temp);
	return (0);
}

static int	absolute_check(char *argv)
{
	char	**abs_bin;

	abs_bin = ft_split(argv, ' ');
	if (!abs_bin)
		return (ft_error("malloc", HAS_ERRNO));
	if (access(abs_bin[0], F_OK | X_OK) != -1)
	{
		free_ptr_array(&abs_bin);
		return (1);
	}
	free_ptr_array(&abs_bin);
	return (0);
}

int	parse_args(char **argv)
{
	char	**all_path;
	char	**arg;
	char	**temp;

	if (absolute_check(argv[3]) == -1)
		return (-1);
	if (absolute_check(argv[3]))
		return (0);
	if (ft_strrchr(argv[3], 39))
		arg = special_case(ft_split(argv[3], 39));
	else
		arg = ft_split(argv[3], ' ');
	if (!arg)
		return (ft_error("malloc", HAS_ERRNO));
	all_path = get_all_path(NULL);
	if (!all_path && free_all(&arg, NULL))
		return (-1);
	temp = find_path(arg, all_path);
	if (!temp && free_all(&arg, &all_path) && free_return(&temp, 1))
		return (-1);
	free_all(&temp, &arg);
	if (check_second_arg(argv, all_path) == -1 && free_return(&all_path, 1))
		return (-1);
	return (free_return(&all_path, 0));
}
