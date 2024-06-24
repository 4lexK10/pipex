/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:55:46 by akloster          #+#    #+#             */
/*   Updated: 2024/06/24 22:22:35 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	piper(char **argv, char *in_path, char *out_path, char **envp)
{
	int		fds[2];
	pid_t	pid;
	int 	status;

	if (pipe(fds) == -1)
		return (ft_error("pipe", HAS_ERRNO));
	pid = fork();
	if (pid == (pid_t ) -1)
		return (ft_error("fork", HAS_ERRNO));
	if (pid == (pid_t) 0)
	{
		if (exec_cmd_parent(argv, fds, in_path, envp) == -1)
			return (-1);
	}
	if (wait(&status) != -1)
	{
		if (exec_cmd_child(argv, fds, out_path, envp) == -1)
			return (-1);
		if (close(fds[1]) == -1)
			return (ft_error("close", HAS_ERRNO));	
		return (0);
	}
	else
		return (ft_error("waitpid", HAS_ERRNO));
}

/* 
	execve(): 
	- env_p needs PATH=/bin
	- (-1) sets errno
	- 
*/
int	main(int argc, char **argv, char **envp)
{
	char	*in_path;
	char	*out_path;

 	if (parse_args(argc, argv, envp) == -1)
		return (-1);
	in_path = ft_strtrim(argv[1], " ");
	out_path = ft_strtrim(argv[4], " ");
	if (!in_path || !out_path)
	{
		my_free(&in_path, 0);
		my_free(&out_path, 0);
		return (ft_error("malloc", HAS_ERRNO));
	}
	if (piper(argv, in_path, out_path, envp) == -1)
		return (-1);
	return (0);
}
