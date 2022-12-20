/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:24:50 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/20 16:01:14 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg_error(int msg)
{
	if (msg == 1)
		write(1, "Please enter 4 or 5 arguments!\n", 31);
	else if (msg == 2)
		write(1, "Malloc secured, please try again!\n", 31);
	else if (msg == 3)
		write(1, "Pthread_create function error!\n", 31);
	else if (msg == 4)
		write(1, "Pthread_join function error!\n", 31);
	return (0);
}
