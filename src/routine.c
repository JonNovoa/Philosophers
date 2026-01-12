/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:07 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/12 14:34:44 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock (philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock (philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_timestamp();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		while (!is_dead(philo->data))
			usleep(1000);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
