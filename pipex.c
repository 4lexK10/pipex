/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:55:46 by akloster          #+#    #+#             */
/*   Updated: 2024/06/21 18:41:52 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	piper(char **argv, char *in_path, char *out_path, char **envp)
{
	/* 	
	int unlink(path): delete file and space it took (-1 sets errno)
	pid_t fork(): creates child (-1 stes errno) succres-> child pid to parent
	int pipe(fds[2]): 
		- 	fills fds with-> fd[0] read_end, fd[1] write_end
		-	needs appropriate close() to all unecessary fd
		-	(-1) sets errno
	int dup2(old_fd, new_fd): sets opened fd to new fd (-1 sets errno)
	pid_t waitpid(pid, &status, options): waits for child to stop (-1 sets errno)

	access: have to split PATH=/ (all the diff path) check with acces
*/
	int		fds[2];
	pid_t	pid;
	pid_t	wpid;
	int 	status;

	if (pipe(fds) == -1)
		return (ft_error("pipe", HAS_ERRNO));
	pid = fork();
	if (pid == (pid_t ) -1)
		return (ft_error("fork", HAS_ERRNO));
	if (pid == (pid_t) 0)
	{
		if (exec_cmd_child(argv, fds, out_path, envp) == -1)
			return (-1);
	}
	if (exec_cmd_parent(argv, fds, in_path, envp) == -1)
		return (-1);
	write(2, "parent\n", 7);
	if (close(fds[1]) == -1)
		return (ft_error("close", HAS_ERRNO));
	wpid = wait(&status);
	if (wpid == pid && status == 0)
		return (0);
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
