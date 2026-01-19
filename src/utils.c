/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:29:28 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/01/19 20:51:53 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophres.h"

long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		mili;

	gettimeofday(&tv, NULL);
	mili = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (mili);
}

long long	get_time_diff(long long start_time)
{
	long long	current;
	long long	dif;

	current = get_timestamp();
	dif = current - start_time;
	return (dif);
}

void	print_status(t_philo *philo, char *status)
{
	long long	dif;
	int			dead;

	dif = get_time_diff(philo->data->start_time);
	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (dead)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", dif, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_usleep(long long milliseconds)
{
	long long	start;
	long long	target;

	start = get_timestamp();
	target = start + milliseconds;
	while (get_timestamp() < target)
		usleep(100);
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->death_flag;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}
