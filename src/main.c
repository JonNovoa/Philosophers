/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:59:35 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/05 18:12:43 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]);
		i++;
	}
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
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

void	*monitor_death(void *arg)
{
	t_data		*data;
	int			i;
	long long	time_since_meal;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			time_since_meal = get_timestamp() - data->philos[i].last_meal_time;
			if (time_since_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->death_flag = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("death");
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}
