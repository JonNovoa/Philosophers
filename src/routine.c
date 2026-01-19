/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:07 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/19 20:51:43 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

int	has_enough_meals(t_philo *philo)
{
	int	done;

	if (philo->data->must_eat_count == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	done = (philo->meals_count >= philo->data->must_eat_count);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (done);
}

void	take_forks(t_philo *philo)
{
	if (has_enough_meals(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
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
			ft_usleep(1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000 / 2);
	while (!is_dead(philo->data) && !has_enough_meals(philo))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		if (has_enough_meals(philo) || is_dead(philo->data))
			break ;
		eat(philo);
		if (has_enough_meals(philo) || is_dead(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
