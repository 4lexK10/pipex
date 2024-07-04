/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:11:41 by akloster          #+#    #+#             */
/*   Updated: 2024/07/03 16:10:35 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *str, int has_errno)
{
	if (has_errno == NO_ERRNO)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	return (-1);
}

int	set_mine(int *mine)
{
	*mine = 1;
	return (1);
}

void	*error_return_null(char *str)
{
	ft_error(str, HAS_ERRNO);
	return (NULL);
}
