/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:36 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 15:40:16 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*ft_check_philo(void *arg)
{
	t_philosopher	*philo;
	t_bool			end_eat;

	end_eat = FALSE;
	philo = (t_philosopher *)arg;
	while (end_eat != TRUE)
	{
		while (philo)
		{
			pthread_mutex_lock(&philo->nocrash);
			if (philo->info.time_to_die <= ft_time() - philo->info.time_to_start
				- philo->last_meal)
			{
				pthread_mutex_unlock(&philo->nocrash);
				ft_put_message(philo, DIE);
				pthread_mutex_lock(&philo->deadischeck);
				philo->dead = TRUE;
				pthread_mutex_unlock(&philo->deadischeck);
				end_eat = TRUE;
				break ;
			}
			pthread_mutex_unlock(&philo->nocrash);
			philo = philo->next;
		}
		philo = (t_philosopher *)arg;
	}
	while (philo)
	{
		pthread_mutex_lock(&philo->deadischeck);
		philo->dead = TRUE;
		pthread_mutex_unlock(&philo->deadischeck);
		philo = philo->next;
	}
	return (NULL);
}
