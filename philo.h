/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 17:23:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_count;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philos;
	pthread_mutex_t	death;
	pthread_t		monitor_thread;
}	t_data;

int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
int			init_philos(t_data *data);
int			start_simulation(t_data *data);
int			destroy_data(t_data *data);
void		*routine(void *arg);
void		print_message(t_philo *philo, char *message);
long long	get_time(void);
int			error(char *message);
int			simulation_stopped(t_data *data);
void		stop_simulation(t_data *data);
int			philo_full(t_data *data);
void		monitor(t_data *data);
int			ft_atoi(const char *str);
void		*monitor_wrapper(void *arg);
int			handle_single_philo(t_philo *philo);
void		get_forks_order(t_philo *philo, int *first, int *second);
int			create_philosopher_threads(t_data *data);
void		join_all_threads(t_data *data);
int			take_both_forks(t_philo *philo, int first, int second);
void		eat_and_release_forks(t_philo *philo, int first, int second);
void		set_high_forks(t_philo *philo, int *first, int *second);
void		set_low_forks(t_philo *philo, int *first, int *second);

#endif