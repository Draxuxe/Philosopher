/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:58:26 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/21 13:55:18 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

t_bool	ft_clear_philo(t_philosopher **philo)
{
	t_philosopher	*tmp;
	t_philosopher	*clear;

	tmp = *philo;
	while (tmp->next)
	{
		clear = tmp;
		tmp = tmp->next;
		free(clear);
	}
	free(tmp);
	return (TRUE);
}

t_bool	ft_clear_info(t_info *info)
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
