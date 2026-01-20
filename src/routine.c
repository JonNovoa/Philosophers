/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:07 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/20 17:39:54 by jnovoa-a         ###   ########.fr       */
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

int	take_forks(t_philo *philo)
{
	if (has_enough_meals(philo))
		return (0);
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
	return (1);
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

static void	handle_single_philo(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	while (!is_dead(philo->data))
		ft_usleep(1000);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (!is_dead(philo->data) && !has_enough_meals(philo))
	{
		print_status(philo, "is thinking");
		if (!take_forks(philo))
			break ;
		if (has_enough_meals(philo) || is_dead(philo->data))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), NULL);
		eat(philo);
		if (has_enough_meals(philo) || is_dead(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
