/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:11:41 by akloster          #+#    #+#             */
/*   Updated: 2024/06/19 17:11:58 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *str, int has_errno)
{
	// void perror(str): prints str (function name) and puts corresponding errno msg
	if (has_errno == NO_ERRNO)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(-1);
	return (-1);
}
