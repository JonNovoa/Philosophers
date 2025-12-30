/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophres.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:40:59 by jnovoa-a          #+#    #+#             */
/*   Updated: 2025/12/30 17:44:50 by marvin           ###   ########.fr       */
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

/*---PARSING---*/
int			ft_atoi(char *str);
int			is_valid_number(char *str);
int			validate_args(int argc, char **argv);
void		parse_args(int argc, char **argv, t_data *data);

/*---INIT---*/
void		init_data(t_data *data);

#endif