/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:20:08 by akloster          #+#    #+#             */
/*   Updated: 2024/06/24 20:24:29 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_ptr_array(char ***s)
{
	int     i;

	if (!**s || !*s)
		return ;
	i = 0;
	if (*s != NULL)
	{
		while ((*s)[i] != NULL)
		{
			free((*s)[i]);
			(*s)[i] = NULL;
			++i;
		}
		free(*s);
		*s = NULL;
	}
}

int     my_free(char **str, int value)
{
		if (!(*str))
				return (1);
		free(*str);
		*str = NULL;
		return (value);
}
