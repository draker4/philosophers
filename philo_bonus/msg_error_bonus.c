/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:36:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 16:30:58 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_all(t_data *data)
{
	if (data->arg)
		free(data->arg);
	if (data->pid_tab)
		free(data->pid_tab);
	if (data->sem)
		if (sem_close(data->sem))
			write(2, "Sem_close function error!\n", 26);
	if (data->sem_write)
		if (sem_close(data->sem_write))
			write(2, "Sem_close function error!\n", 26);
	if (data->sem_stop)
		if (sem_close(data->sem_stop))
			write(2, "Sem_close function error!\n", 26);
	if (data->sem_meals)
		if (sem_close(data->sem_meals))
			write(2, "Sem_close function error!\n", 26);
	free(data);
}

int	msg_error(int msg, t_data *data)
{
	if (msg == 1)
		write(2, "Please enter 4 or 5 arguments!\n", 31);
	else if (msg == 2)
		write(2, "Malloc secured, please try again!\n", 34);
	else if (msg == 3)
		write(2, "At least one philosopher has to be sitting down!\n", 49);
	else if (msg == 4)
		write(2, "Fork function error!\n", 21);
	else if (msg == 5)
		write(2, "Waitpid function error!\n", 24);
	else if (msg == 6)
		write(2, "Kill function error!\n", 21);
	else if (msg == 7)
		write(2, "Sem_unlink function error!\n", 27);
	if (data)
		free_all(data);
	return (0);
}
