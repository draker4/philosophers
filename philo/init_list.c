/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:58:47 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:53:29 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data **data)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < (*data)->arg->nb_total_philo)
	{
		if (pthread_mutex_init(&(*data)->info->forks[i], NULL))
		{
			error = 1;
			write(2, "Pthread_mutex_init function error\n", 34);
		}
		if (pthread_mutex_init(&(*data)->info->neighbourgs[i++], NULL))
		{
			error = 1;
			write(2, "Pthread_mutex_init function error\n", 34);
		}
	}
	if (error)
		return (msg_error(0, NULL, data));
	return (1);
}

static void	fill_data(t_data **data)
{
	t_data	*current;
	t_data	*previous;
	t_data	*first;

	current = *data;
	first = current;
	previous = NULL;
	while (current->next)
	{
		current->next_circ = current->next;
		current->prev_circ = previous;
		previous = current;
		current = current->next;
	}
	current->prev_circ = previous;
	current->next_circ = first;
	first->prev_circ = current;
}

int	create_lst_data(t_data **data, t_arg *arg, t_info *info)
{
	int		i;
	t_data	*current;

	i = 0;
	while (i < arg->nb_total_philo)
	{
		current = create_new(i, arg, info);
		if (!current)
		{
			free(arg);
			free(info->forks);
			free(info->neighbourgs);
			free(info);
			lst_clear(data);
			return (0);
		}
		lst_add_back(data, current);
		i++;
	}
	fill_data(data);
	return (1);
}
