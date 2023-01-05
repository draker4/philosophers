/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:36:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/05 14:33:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	msg_error(int msg, t_arg *arg, pid_t *pid)
{
	if (msg == 1)
		write(2, "Please enter 4 or 5 arguments!\n", 31);
	else if (msg == 2)
		write(2, "Malloc secured, please try again!\n", 34);
	else if (msg == 3)
		write(2, "At least one philosopher has to be sitting down!\n", 49);
	else if (msg == 4)
		write(2, "Fork function error!\n", 21);
	if (arg)
		free(arg);
	if (pid)
		free(pid);
	return (0);
}
