/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:43:07 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/05 18:03:40 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

int	check_philosopher_death(t_data *data, int i)
{
	long long	time_since_meal;

	time_since_meal = get_timestamp() - data->philos[i].last_meal_time;
	if (time_since_meal > data->philos[i].last_meal_time)
		return (1);
	return (0);
}

void	handle_death(t_data *data, int i)
{
	pthread_mutex_lock(data->death_flag);
	data->death_flag = 1;
	pthread_mutex_unlock(data->death_flag);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n", get_time_diff(data->start_time),
		data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philosopher_death(data, i))
			{
				handle_death(data, i);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}
