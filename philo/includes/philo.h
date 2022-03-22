/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:08:51 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 17:00:33 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define THINK 10
# define EAT 11
# define DIE 12
# define SLEEP 13
# define FORK 14

typedef int	t_bool;

typedef struct s_info {
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	long long int			time_to_start;
	int						number_of_times_each_philosopher_must_eat;
	pthread_mutex_t			*forks;
	pthread_mutex_t			*writter;
}				t_info;

typedef struct s_philosopher {
	pthread_t				monitor;
	pthread_t				thread_philo;
	pthread_mutex_t			nocrash;
	pthread_mutex_t			deadischeck;
	pthread_mutex_t			lastmealcheck;
	int						value;
	int						last_meal;
	int						id;
	int						number_of_eat;
	t_info					info;
	t_bool					dead;
	struct s_philosopher	*next;
}				t_philosopher;

int					ft_atoi(const char *str);
t_bool				ft_init_info(int argc, char **argv, t_info *info);
t_bool				ft_init_philo(t_philosopher **philo, t_info info);
t_bool				ft_clear_philo(t_philosopher **philo);
void				ft_launcher(t_philosopher *philo);

/** ft_utils **/
void				ft_putnbr(int nb);
void				ft_putstr(char *str);
void				ft_put_message(t_philosopher *philo, int message);
long long int		ft_time(void);
void				ft_smart_usleep(int time);

/** ft_routine **/
void				ft_take_fork(t_philosopher *philo);
void				ft_eat(t_philosopher *philo);
void				ft_sleep(t_philosopher *philo);
void				*ft_dead(void *arg);

/** ft_clear **/
t_bool				ft_clear_info(t_info *info);

/** ft_routine **/
void				*routine(void *arg);

/** ft_check_philo **/
void				*ft_check_philo(void *arg);

#endif