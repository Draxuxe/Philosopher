/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:58:26 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 13:46:17 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

t_bool	clear_philo(t_philosopher **philo)
{
	t_philosopher	*tmp;
	t_philosopher	*clear;

	tmp = *philo;
	while (tmp->next)
	{
		clear = tmp;
		tmp = tmp->next;
		pthread_mutex_destroy(&clear->deadischeck);
		pthread_mutex_destroy(&clear->lastmealcheck);
		pthread_mutex_destroy(&clear->nocrash);
		free(clear);
	}
	free(tmp);
	return (TRUE);
}

t_bool	clear_info(t_info *info)
{
	int	index;

	index = -1;
	while (++index < info->number_of_philosophers)
		pthread_mutex_destroy(&info->forks[index]);
	pthread_mutex_destroy(info->writter);
	free(info->forks);
	free(info->writter);
	return (TRUE);
}
