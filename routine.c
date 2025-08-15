/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahajj-h <mahajj-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 19:22:49 by mahajj-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_and_join_threads(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL, monitor_wrapper, data) != 0)
	{
		error("Failed to create monitor thread");
		return (0);
	}
	if (!create_philosopher_threads(data))
		return (0);
	return (1);
}

int	start_simulation(t_data *data)
{
	return (create_and_join_threads(data));
}

int	take_forks_and_eat(t_philo *philo, int first, int second)
{
	if (!take_both_forks(philo, first, second))
		return (0);
	eat_and_release_forks(philo, first, second);
	return (1);
}

int	handle_eating(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo));
	get_forks_order(philo, &first_fork, &second_fork);
	return (take_forks_and_eat(philo, first_fork, second_fork));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (!simulation_stopped(philo->data))
	{
		if (philo->data->meals_to_eat != -1
			&& philo->meals_count >= philo->data->meals_to_eat)
			break ;
		print_message(philo, "is thinking");
		if (philo->data->num_philos % 2 == 1)
			usleep(philo->data->time_to_eat * 500);
		if (simulation_stopped(philo->data))
			break ;
		if (!handle_eating(philo))
			break ;
		if (simulation_stopped(philo->data))
			break ;
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}
