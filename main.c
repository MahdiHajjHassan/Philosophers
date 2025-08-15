/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahajj-h <mahajj-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:04:57 by mahajj-h          #+#    #+#             */
/*   Updated: 2025/07/30 19:26:34 by mahajj-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	setup_simulation(int argc, char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (!parse_args(argc, argv, data))
		return (error("Error: Invalid arguments"));
	if (!init_data(data))
	{
		destroy_data(data);
		return (error("Error: Failed to initialize data"));
	}
	data->start_time = get_time();
	if (!start_simulation(data))
	{
		destroy_data(data);
		return (error("Error: Failed to start simulation"));
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!setup_simulation(argc, argv, &data))
		return (1);
	join_all_threads(&data);
	destroy_data(&data);
	return (0);
}
