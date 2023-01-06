/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:33:20 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 16:12:50 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	write_msg(char *str, t_data *data, int time, int death)
{
	if (sem_wait(data->sem_write))
		write(2, "Sem_wait function error!\n", 25);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(data->index, 1);
	write(1, str, ft_strlen(str));
	if (!death)
	{
		if (sem_post(data->sem_write))
			write(2, "Sem_post function error!\n", 25);
	}
}
