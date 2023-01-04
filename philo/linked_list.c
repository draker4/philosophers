/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:36:02 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/03 18:33:37 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*create_new(int index, t_arg *arg, t_info *info)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->nb_meals = 0;
	new->index = index;
	new->t_begin_eat = 0;
	new->t_begin_sleep = 0;
	new->info = info;
	new->next_circ = 0;
	new->prev_circ = 0;
	new->arg = arg;
	return (new);
}

void	lst_add_back(t_data **data, t_data *to_add)
{
	t_data	*current;

	if (data && *data)
	{
		current = *data;
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
	else if (data)
		*data = to_add;
}

void	lst_clear(t_data **data)
{
	t_data	*current;
	t_data	*previous;

	current = *data;
	while (current)
	{
		previous = current;
		current = current->next;
		free(previous);
	}
	*data = NULL;
}
