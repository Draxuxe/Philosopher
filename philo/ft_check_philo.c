/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:36 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 16:54:55 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_all_dead(t_philosopher *philo)
{	
	while (philo)
	{
		pthread_mutex_lock(&philo->deadischeck);
		philo->dead = TRUE;
		pthread_mutex_unlock(&philo->deadischeck);
		philo = philo->next;
	}
}

t_bool	ft_is_dead(t_philosopher *philo)
{
	if (philo->info.time_to_die <= ft_time() - philo->info.time_to_start
		- philo->last_meal)
	{
		pthread_mutex_unlock(&philo->nocrash);
		ft_put_message(philo, DIE);
		pthread_mutex_lock(&philo->deadischeck);
		philo->dead = TRUE;
		pthread_mutex_unlock(&philo->deadischeck);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_is_full_meal(t_philosopher *philo)
{
	if (philo->info.number_of_times_each_philosopher_must_eat == -1)
		return (FALSE);
	while (philo)
	{
		pthread_mutex_lock(&philo->lastmealcheck);
		if (philo->number_of_eat
			< philo->info.number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&philo->lastmealcheck);
			return (FALSE);
		}	
		pthread_mutex_unlock(&philo->lastmealcheck);
		philo = philo->next;
	}
	return (TRUE);
}

void	*ft_check_philo(void *arg)
{
	t_philosopher	*philo;
	t_bool			end_time;
	t_bool			end_full_meal;

	end_time = FALSE;
	end_full_meal = FALSE;
	philo = (t_philosopher *)arg;
	while (end_time != TRUE && end_full_meal != TRUE)
	{
		while (philo)
		{
			pthread_mutex_lock(&philo->nocrash);
			if (ft_is_dead(philo) == TRUE)
			{
				end_time = TRUE;
				break ;
			}
			pthread_mutex_unlock(&philo->nocrash);
			philo = philo->next;
		}
		philo = (t_philosopher *)arg;
		end_full_meal = ft_is_full_meal(philo);
	}
	ft_all_dead(philo);
	return (NULL);
}