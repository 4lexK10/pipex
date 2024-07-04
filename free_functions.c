/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:20:08 by akloster          #+#    #+#             */
/*   Updated: 2024/07/04 13:32:01 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_all(char ***arg, char ***all_path)
{
	free_ptr_array(arg);
	free_ptr_array(all_path);
	return (1);
}

void	free_ptr_array(char ***s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return ;
	if (**s)
	{
		while ((*s)[i] != NULL)
		{
			free((*s)[i]);
			(*s)[i] = NULL;
			++i;
		}
	}
	free(*s);
	*s = NULL;
}

int	exec_free_all(char ***arg, char ***check, char **bin_path)
{
	free_ptr_array(arg);
	free_ptr_array(check);
	my_free(bin_path, 0);
	return (1);
}

int	free_return(char ***s, int value)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (value);
	if (**s)
	{
		while ((*s)[i] != NULL)
		{
			free((*s)[i]);
			(*s)[i] = NULL;
			++i;
		}
	}
	free(*s);
	*s = NULL;
	return (value);
}

int	my_free(char **str, int value)
{
	if (!str || !*str)
		return (value);
	free(*str);
	*str = NULL;
	return (value);
}
