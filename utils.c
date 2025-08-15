/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 16:32:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print);
	if (!simulation_stopped(philo->data))
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long time_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_ms)
	{
		if (simulation_stopped(data))
			return ;
		usleep(100);
	}
}

int	error(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(2, message, i);
	write(2, "\n", 1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647 || (sign == -1 && result > 2147483648))
			return (0);
		i++;
	}
	return (sign * result);
}
