/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahajj-h <mahajj-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 19:11:32 by mahajj-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	while (!simulation_stopped(philo->data))
		usleep(1000);
	return (0);
}

int	take_both_forks(t_philo *philo, int first, int second)
{
	while (!simulation_stopped(philo->data))
	{
		pthread_mutex_lock(&philo->data->forks[first]);
		if (simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[first]);
			return (0);
		}
		pthread_mutex_lock(&philo->data->forks[second]);
		if (simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[second]);
			pthread_mutex_unlock(&philo->data->forks[first]);
			return (0);
		}
		print_message(philo, "has taken a fork");
		print_message(philo, "has taken a fork");
		return (1);
	}
	return (0);
}

void	eat_and_release_forks(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[second]);
	pthread_mutex_unlock(&philo->data->forks[first]);
}

void	set_high_forks(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork > philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	set_low_forks(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}
