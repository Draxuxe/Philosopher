/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:21:08 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 11:54:24 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

static void	wait_pair(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
		usleep(500);
}

void	take_fork(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->info.forks[philo->id - 1]);
	pthread_mutex_lock(&philo->info.forks[philo->id]);
	put_message(philo, FORK);
	put_message(philo, FORK);
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->nocrash);
	philo->last_meal = get_time() - philo->info.time_to_start;
	pthread_mutex_unlock(&philo->nocrash);
	pthread_mutex_lock(&philo->nocrash);
	put_message(philo, EAT);
	pthread_mutex_unlock(&philo->nocrash);
	smart_usleep(philo->info.time_to_eat);
	pthread_mutex_unlock(&philo->info.forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->info.forks[philo->id]);
	pthread_mutex_lock(&philo->lastmealcheck);
	if (philo->info.number_of_times_each_philosopher_must_eat != -1)
		philo->number_of_eat++;
	pthread_mutex_unlock(&philo->lastmealcheck);
}

void	go_sleep(t_philosopher *philo)
{
	put_message(philo, SLEEP);
	smart_usleep(philo->info.time_to_sleep);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	put_message(philo, THINK);
	if (philo->info.number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->info.forks[philo->id - 1]);
		put_message(philo, FORK);
	}
	wait_pair(philo);
	while (1 && philo->info.number_of_philosophers != 1)
	{
		take_fork(philo);
		eat(philo);
		put_message(philo, THINK);
		go_sleep(philo);
		pthread_mutex_lock(&philo->deadischeck);
		if (philo->dead == TRUE)
			break ;
		pthread_mutex_unlock(&philo->deadischeck);
	}
	pthread_mutex_unlock(&philo->deadischeck);
	return (NULL);
}
