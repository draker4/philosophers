/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:27:28 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/09 10:46:24 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg->nb_total_philo)
	{
		if (sem_wait(data->sem_meals))
			write(2, "Sem_wait function error!\n", 25);
		i++;
	}
	if (sem_wait(data->sem_write))
		write(2, "Sem_wait function error!\n", 25);
	if (sem_post(data->sem_stop))
		write(2, "Sem_post function error!\n", 25);
	while (1)
		;
}

static void	child_routine(t_data *data)
{
	int	time;

	if (data->index == data->arg->nb_total_philo + 1)
		check_meals(data);
	time = get_time(data);
	if (data->arg->nb_total_philo == 1)
	{
		philo_one_fork(data);
		while (is_not_dead(data, time))
			time = get_time(data);
	}
	else
	{
		while (is_not_dead(data, time))
		{
			philo_wait_forks(data);
			philo_eat(data);
			philo_sleep(data);
			time = get_time(data);
		}
	}
	write_msg(" died\n", data, time, 1);
	if (sem_post(data->sem_stop))
		write(2, "Sem_post function error!\n", 25);
}

static int	create_philos(t_data *data, int *pid)
{
	int	i;

	i = 0;
	while (i < data->arg->nb_total_philo + 1)
	{
		data->index = i + 1;
		data->pid_tab[i] = fork();
		*pid = data->pid_tab[i];
		if (data->pid_tab[i] == -1)
		{
			while (--i)
			{
				if (kill(data->pid_tab[i], SIGKILL) == -1)
					write(2, "kill function error!\n", 21);
			}
			return (msg_error(4, data));
		}
		else if (!data->pid_tab[i])
			break ;
		i++;
	}
	return (1);
}

static int	parent_routine(t_data *data)
{
	int	i;

	i = 0;
	if (sem_wait(data->sem_stop))
		write(2, "Sem_wait function error!\n", 25);
	while (i < data->arg->nb_total_philo + 1)
	{
		if (kill(data->pid_tab[i], SIGKILL) == -1)
			write(2, "kill function error!\n", 21);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	pid_t	pid;

	data = malloc(sizeof(t_data));
	if (!data)
		return (msg_error(2, NULL));
	if (!initialize(data, argc, argv))
		return (0);
	init_time(data);
	if (!create_philos(data, &pid))
		return (0);
	if (!pid)
		child_routine(data);
	else
	{
		if (!parent_routine(data))
			return (msg_error(0, data));
	}
	return (msg_error(0, data));
}
