/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:21:26 by akloster          #+#    #+#             */
/*   Updated: 2024/06/24 19:07:22 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* HAVE TO PARSE ENVP with access*/

static int	check_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_isalnum(str[i]))
			return (0);
	}
	return (ft_error("error: incorrect argument", NO_ERRNO));
}

int	parse_args(int argc, char **argv, char **envp)
{
	char	**all_path;
	char	**arg;

	if (argc != 5)
		return (ft_error("error: incorrect number of arguments",
			NO_ERRNO));
	if (!envp)
		return (ft_error("error: missing environment variables",
			NO_ERRNO));
	if (check_arg(argv[2]) == -1 || check_arg(argv[3]) == -1)
		return (-1);
	arg = ft_split(argv[3], ' ');
	if (!arg)
		return (ft_error("malloc", HAS_ERRNO));
	all_path = get_all_path(envp);
	if (!all_path)
	{
		free_ptr_array(&arg);
		return (-1);
	}
	if (!find_path(arg, all_path))
		return (-1);
	return (0);
}

