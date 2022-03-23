/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:08:51 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 12:07:20 by lfilloux         ###   ########.fr       */
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

/** Algo **/
int					ft_atoi(const char *str);
t_bool				init_info(int argc, char **argv, t_info *info);
t_bool				init_philo(t_philosopher **philo, t_info info);
void				launcher(t_philosopher *philo);
/** Utils **/
void				ft_putnbr(int nb);
void				ft_putstr(char *str);
void				put_message(t_philosopher *philo, int message);
long long int		get_time(void);
void				smart_usleep(int time);
/** Routine **/
void				*routine(void *arg);
void				take_fork(t_philosopher *philo);
void				eat(t_philosopher *philo);
void				go_sleep(t_philosopher *philo);
void				*dead(void *arg);
/** Clear **/
t_bool				clear_philo(t_philosopher **philo);
t_bool				clear_info(t_info *info);
/** Check **/
void				*check_philo(void *arg);

#endif