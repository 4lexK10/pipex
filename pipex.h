/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:42:38 by akloster          #+#    #+#             */
/*   Updated: 2024/06/19 18:27:49 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
#include <stdio.h>
# define HAS_ERRNO 1
# define NO_ERRNO 0

void    free_ptr_array(char ***s);
int     my_free(char **str, int value);
int     ft_error(char *str, int has_errno);
int     child_files(int *fds, char *path);
int     parent_files(int *fds, char *path);
int     exec_cmd_child(char **argv, int *fds, char *path);
int     exec_cmd_parent(char **argv, int *fds, char *path);


#endif

