/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:50:52 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 14:30:17 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_data **data)
{
	struct timeval	tp;
	int				time;

	if (gettimeofday(&tp, NULL))
		write(2, "GetTimeOfDay function error\n", 28);
	if ((*data)->info->init_time.s == tp.tv_sec)
		time = (tp.tv_usec - (*data)->info->init_time.mu_s) / 1000;
	else
	{
		time = (tp.tv_sec - ((*data)->info->init_time.s + 1)) * 1000000;
		time += 1000000 - (*data)->info->init_time.mu_s;
		time += tp.tv_usec;
		time /= 1000;
	}
	// if (time < 0)
	//  	printf("index = %d et timeday = %ld et %d et time = %d\n", (*data)->index + 1, tp.tv_sec, tp.tv_usec, time);
	//  if (time < 0)
	//  	printf("time init = %d et %d\n", (*data)->info->init_time.s, (*data)->info->init_time.mu_s);
	return (time);
}
