/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:36:59 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 12:09:03 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	launcher(t_philosopher *philo)
{
	int				err;
	t_philosopher	*tmp;

	tmp = philo;
	while (tmp)
	{
		err = pthread_create(&tmp->thread_philo, NULL, routine, tmp);
		if (err)
			pthread_detach(tmp->thread_philo);
		tmp = tmp->next;
	}
	tmp = philo;
	err = pthread_create(&tmp->monitor, NULL, check_philo, tmp);
	if (err)
		pthread_detach(tmp->monitor);
	while (tmp)
	{
		pthread_join(tmp->thread_philo, NULL);
		tmp = tmp->next;
	}
	tmp = philo;
	pthread_join(tmp->monitor, NULL);
}
