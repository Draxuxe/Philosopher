/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:23:26 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 17:44:50 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

t_philosopher	*ft_add_new_philo(t_info info, int index)
{
	t_philosopher	*new;

	new = malloc(sizeof (t_philosopher));
	if (!new)
		exit(EXIT_FAILURE);
	new->info = info;
	new->last_meal = 0;
	new->number_of_eat = 0;
	new->dead = FALSE;
	new->next = NULL;
	new->value = 0;
	new->id = index;
	pthread_mutex_init(&new->nocrash, NULL);
	pthread_mutex_init(&new->deadischeck, NULL);
	pthread_mutex_init(&new->lastmealcheck, NULL);
	return (new);
}

void	ft_add_back_philo(t_philosopher **philo, t_philosopher *new)
{
	t_philosopher	*tmp;

	if (!*philo)
		*philo = new;
	else
	{
		tmp = *philo;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_bool	ft_init_philo(t_philosopher **philo, t_info info)
{
	int	index;

	index = 0;
	while (++index <= info.number_of_philosophers)
		ft_add_back_philo(philo, ft_add_new_philo(info, index));
	return (TRUE);
}
