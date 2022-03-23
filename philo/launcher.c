/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:36:59 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 14:09:10 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	launcher(t_philosopher *philo)
{
	t_philosopher	*tmp;

	tmp = philo;
	while (tmp)
	{
		if (pthread_create(&tmp->thread_philo, NULL, routine, tmp))
			return ;
		if (pthread_detach(tmp->thread_philo))
			return ;
		tmp = tmp->next;
	}
	tmp = philo;
	if (pthread_create(&tmp->monitor, NULL, check_philo, tmp))
		if (pthread_detach(tmp->monitor))
			return ;
	while (tmp)
	{
		pthread_join(tmp->thread_philo, NULL);
		tmp = tmp->next;
	}
	tmp = philo;
	pthread_join(tmp->monitor, NULL);
}
