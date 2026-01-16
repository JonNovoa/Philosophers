/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:59:35 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/16 19:10:27 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

int	start_simulation(t_data *data, pthread_t *monitor)
{
	int			i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_death, data);
	return (1);
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	monitor;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: malloc\n", 14), 1);
	if (!validate_args(argc, argv))
		return (write(2, "Error: args\n", 12), free(data), 1);
	parse_args(argc, argv, data);
	if (!init_data(data))
		return (write(2, "Error: init\n", 12), free(data), 1);
	start_simulation(data, &monitor);
	wait_threads(data);
	pthread_join(monitor, NULL);
	cleanup(data);
	free(data);
	return (0);
}
