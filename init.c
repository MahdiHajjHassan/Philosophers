/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 17:14:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	cleanup_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

int	init_other_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		cleanup_fork_mutexes(data);
		return (0);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		cleanup_fork_mutexes(data);
		return (0);
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].meals_count = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
			free(data->philos);
			data->philos = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_data(t_data *data)
{
	data->stop = 0;
	data->start_time = get_time();
	if (!init_fork_mutexes(data))
		return (0);
	if (!init_other_mutexes(data))
		return (0);
	if (!init_philos(data))
	{
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->print);
		cleanup_fork_mutexes(data);
		return (0);
	}
	return (1);
}
