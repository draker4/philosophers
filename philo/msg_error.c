/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:24:50 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 15:29:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_data **data)
{
	if (data)
	{
		if ((*data)->info)
		{
			destroy_mutex(data);
			free((*data)->info->forks);
			if ((*data)->info->philos)
				free((*data)->info->philos);
			free((*data)->info);
		}
		if ((*data)->arg)
			free((*data)->arg);
		lst_clear(data);
	}
}

int	msg_error(int msg, t_data **data)
{
	if (msg == 1)
		write(2, "Please enter 4 or 5 arguments!\n", 31);
	else if (msg == 2)
		write(2, "Malloc secured, please try again!\n", 34);
	else if (msg == 3)
		write(2, "At least one philosopher has to be sitting down!\n", 49);
	else if (msg == 4)
		write(2, "Pthread_mutex_init function error\n", 34);
	free_all(data);
	return (0);
}
