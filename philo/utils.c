/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:31:06 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/05 13:24:02 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_overflow(int sign)
{
	if (sign < 0)
		return ((int)LONG_MIN);
	else
		return ((int)LONG_MAX);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != (result * 10 + str[i] - 48) / 10)
			return (ft_overflow(sign));
		else
			result = result * 10 + str[i] - 48;
		i++;
	}
	return ((int)(result * sign));
}

void	write_msg(char *str, t_data **data, int time)
{
	if (pthread_mutex_lock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd((*data)->index + 1, 1);
	write(1, str, ft_strlen(str));
	if (pthread_mutex_unlock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
}

void	set_begin(t_data **data)
{
	if (pthread_mutex_lock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	(*data)->info->begin += 1;
	if (pthread_mutex_unlock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
}

int	get_begin(t_data **data)
{
	int	begin;

	if (pthread_mutex_lock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	begin = (*data)->info->begin;
	if (pthread_mutex_unlock(&(*data)->info->mutex_write))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
	return (begin);
}
