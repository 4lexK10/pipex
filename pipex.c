/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:55:46 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 13:31:31 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent_finish(int fds[2], pid_t pid1, pid_t pid2)
{
	if (close(fds[0]) == -1 || close(fds[1]) == -1)
		return (ft_error("close", HAS_ERRNO));
	if (waitpid(pid1, NULL, 0) == -1 || waitpid(pid2, NULL, 0) == -1)
		return (ft_error("waitpid", HAS_ERRNO));
	return (0);
}

static int	piper(char **argv, char *in_path, char *out_path, char **envp)
{
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fds) == -1)
		return (ft_error("pipe", HAS_ERRNO));
	pid1 = fork();
	if (pid1 == (pid_t) -1)
		return (ft_error("fork", HAS_ERRNO));
	if (pid1 == (pid_t) 0)
	{
		if (first_files(fds, in_path) == -1 || exec_cmd(argv[2], envp) == -1)
			return (-1);
	}
	pid2 = fork();
	if (pid2 == (pid_t) -1)
		return (ft_error("fork", HAS_ERRNO));
	if (pid2 == (pid_t) 0)
	{
		if (second_files(fds, out_path) == -1 || parse_args(argv) == -1)
			return (-1);
		if (exec_cmd(argv[3], envp) == -1)
			return (-1);
	}
	return (parent_finish(fds, pid1, pid2));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_error("error: incorrect number of arguments", 0));
	if (piper(argv, argv[1], argv[4], envp) == -1)
		return (-1);
	return (0);
}
