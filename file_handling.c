/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:12:42 by akloster          #+#    #+#             */
/*   Updated: 2024/06/19 18:59:24 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_files(int *fds, char *path)
{
	int	output_fd;

	write(1, "child\n", 6);
	if (access(path, W_OK) == -1)
		return (ft_error("access", HAS_ERRNO));
	output_fd = open(path, O_WRONLY | O_TRUNC);
	if (output_fd == -1)
		return (ft_error("open", HAS_ERRNO));
	if (dup2(fds[0], STDIN_FILENO) == -1 ||
			dup2(output_fd, STDOUT_FILENO) == -1)
		return (ft_error("dup2", HAS_ERRNO));
	if (close(fds[1]) == -1 || close(fds[0]) == -1)
		return (ft_error("close", HAS_ERRNO));
	return (0);
}

int parent_files(int *fds, char *path)
{
	int	input_fd;

	write(1, "parent\n", 7);
	if (access(path, R_OK) == -1)
		return (ft_error("access", HAS_ERRNO));
	input_fd = open(path, O_RDONLY);
	if (input_fd == -1)
		return (ft_error("open", HAS_ERRNO));
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (ft_error("dup2", HAS_ERRNO));
	if (close(fds[0]) == -1)
		return (ft_error("close", HAS_ERRNO));
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", HAS_ERRNO));
	return (0);
}
