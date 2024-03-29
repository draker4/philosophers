/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:58:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 12:05:22 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
