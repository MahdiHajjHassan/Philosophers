/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahajj-h <mahajj-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 19:22:09 by mahajj-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_to_eat <= 0)
		return (0);
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_count < data->meals_to_eat)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->stop = 1;
	pthread_mutex_unlock(&data->death);
}

int	simulation_stopped(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->death);
	ret = data->stop;
	pthread_mutex_unlock(&data->death);
	return (ret);
}

int	check_death(t_data *data, int i)
{
	long long	time_diff;
	t_philo		*philo;

	philo = &data->philos[i];
	pthread_mutex_lock(&philo->meal_mutex);
	time_diff = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_diff >= data->time_to_die)
	{
		stop_simulation(data);
		pthread_mutex_lock(&data->print);
		printf("%lld %d died\n", get_time() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int	i;

	while (!simulation_stopped(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_death(data, i))
				return ;
			i++;
		}
		if (philo_full(data))
		{
			stop_simulation(data);
			return ;
		}
		ft_usleep(2, data);
	}
}
