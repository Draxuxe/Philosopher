/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:21:08 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 17:48:59 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_wait_pair(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
		usleep(500);
}

void	ft_take_fork(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->info.forks[philo->id - 1]);
	pthread_mutex_lock(&philo->info.forks[philo->id]);
	pthread_mutex_lock(&philo->nocrash);
	philo->last_meal = ft_time() - philo->info.time_to_start;
	pthread_mutex_unlock(&philo->nocrash);
	ft_put_message(philo, FORK);
	ft_put_message(philo, FORK);
}

void	ft_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->nocrash);
	ft_put_message(philo, EAT);
	pthread_mutex_unlock(&philo->nocrash);
	ft_smart_usleep(philo->info.time_to_eat);
	pthread_mutex_unlock(&philo->info.forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->info.forks[philo->id]);
	pthread_mutex_lock(&philo->lastmealcheck);
	if (philo->info.number_of_times_each_philosopher_must_eat != -1)
		philo->number_of_eat++;
	pthread_mutex_unlock(&philo->lastmealcheck);
}

void	ft_sleep(t_philosopher *philo)
{
	ft_put_message(philo, SLEEP);
	ft_smart_usleep(philo->info.time_to_sleep);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	ft_put_message(philo, THINK);
	if (philo->info.number_of_philosophers == 1)
		ft_put_message(philo, FORK);
	ft_wait_pair(philo);
	while (1 && philo->info.number_of_philosophers != 1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_put_message(philo, THINK);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->deadischeck);
		if (philo->dead == TRUE)
			break ;
		pthread_mutex_unlock(&philo->deadischeck);
	}
	pthread_mutex_unlock(&philo->deadischeck);
	return (NULL);
}
