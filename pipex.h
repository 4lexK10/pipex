/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:42:38 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 13:32:48 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# define HAS_ERRNO 1
# define NO_ERRNO 0

void	free_ptr_array(char ***s);
int		my_free(char **str, int value);
int		ft_error(char *str, int has_errno);
int		second_files(int *fds, char *path);
int		first_files(int *fds, char *path);
int		exec_cmd(char *argv, char **envp);
int		parse_args(char **argv);
char	**get_all_path(char **envp);
char	**find_path(char **bin, char **envp);
char	*complete_path(char *path);
char	**get_all_path(char **envp);
char	**find_path(char **bin, char **envp);
int		free_return(char ***s, int value);
char	**special_case(char **arg);
int		set_mine(int *mine);
void	*error_return_null(char *str);
int		exec_free_all(char ***arg, char ***check, char **bin_path);
char	**get_full_arg(char **argv);
int		free_all(char ***arg, char ***all_path);

#endif
