/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:36:59 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/21 15:38:23 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_launcher(t_philosopher *philo)
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
	err = pthread_create(&tmp->monitor, NULL, ft_check_philo, tmp);
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
