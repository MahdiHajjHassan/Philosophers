/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 17:26:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_wrapper(void *arg)
{
	monitor((t_data *)arg);
	return (NULL);
}

void	get_forks_order(t_philo *philo, int *first, int *second)
{
	*first = philo->left_fork;
	*second = philo->right_fork;
}

int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			stop_simulation(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			pthread_join(data->monitor_thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
}
