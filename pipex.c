/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:55:46 by akloster          #+#    #+#             */
/*   Updated: 2024/06/19 18:28:13 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* int	parse_args(int argc, char **argv)
{
	// int acces(path, int mode): check files with (-1 sets errno)
	// envp and argv limmited byt ARG_MAX
	if (ARG_MAX)
	;
} */

int	piper(char **argv, char *in_path, char *out_path)
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
		if (exec_cmd_child(argv, fds, out_path) == -1)
			return (-1);
	}
	if (exec_cmd_parent(argv, fds, in_path) == -1)
		return (-1);
	if (close(fds[1]) == -1)
		return (ft_error("close", HAS_ERRNO));
	wpid = waitpid(pid, &status, 0);
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
int	main(int argc, char **argv)
{
	char	*in_path;
	char	*out_path;

	if (argc != 5)
		return (ft_error("error: incorrect number of arguents", NO_ERRNO));
/* 	if (parse_args(argc, argv))
		; */
	in_path = ft_strtrim(argv[1], " \t");
	out_path = ft_strtrim(argv[4], " \t");
	if (!in_path || !out_path)
	{
		my_free(&in_path, 0);
		my_free(&out_path, 0);
		return (ft_error("malloc", HAS_ERRNO));
	}
	if (piper(argv, in_path, out_path) == -1)
		return (-1);
	system("leaks pipex");
	return (0);
}