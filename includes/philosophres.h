/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophres.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:40:59 by jnovoa-a          #+#    #+#             */
/*   Updated: 2025/12/29 19:54:07 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHRES_H
# define PHILOSOPHRES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h> 

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				death_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;


/*---UTILS---*/

long long	get_timestamp(void);
long long	get_time_diff(long long start_time);
void		print_status(t_philo *philo, char *status);
void		ft_usleep(long long milliseconds);
int			is_dead(t_data *data);

#endif