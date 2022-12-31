/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:24:50 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/29 20:04:52 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(pthread_t *philos, t_data **data)
{
	if (data)
	{
		if ((*data)->info)
		{
			if ((*data)->info->forks)
				free((*data)->info->forks);
			if ((*data)->info->neighbourgs)
				free((*data)->info->neighbourgs);
			free((*data)->info);
		}
		if ((*data)->arg)
			free((*data)->arg);
		lst_clear(data);
	}
	if (philos)
		free(philos);
}

int	msg_error(int msg, pthread_t *philos, t_data **data)
{
	if (msg == 1)
		write(2, "Please enter 4 or 5 arguments!\n", 31);
	else if (msg == 2)
		write(2, "Malloc secured, please try again!\n", 34);
	else if (msg == 3)
		write(2, "At least one philosopher has to be sitting down!\n", 34);
	free_all(philos, data);
	return (0);
}
