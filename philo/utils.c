/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:26:57 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 11:01:52 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

void	ft_putnbr(int nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		nb = nb + 48;
		write(1, &nb, 1);
	}
}

void	ft_putstr(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
		write(1, &str[index], 1);
}

void	put_message(t_philosopher *philo, int message)
{
	int		actu_time;

	pthread_mutex_lock(&philo->deadischeck);
	pthread_mutex_lock(philo->info.writter);
	if (philo->dead == FALSE)
	{	
		actu_time = get_time() - philo->info.time_to_start;
		if (message == THINK)
			printf("%d ms philo numero %d is thinking\n", actu_time, philo->id);
		else if (message == SLEEP)
			printf("%d ms philo numero %d is sleeping\n", actu_time, philo->id);
		else if (message == FORK)
			printf("%d ms philo numero %d has taken a fork\n",
				actu_time, philo->id);
		else if (message == EAT)
			printf("%d ms philo numero %d is eating\n", actu_time, philo->id);
		else if (message == DIE)
			printf("%d ms philo numero %d died\n", actu_time, philo->id);
	}
	pthread_mutex_unlock(philo->info.writter);
	pthread_mutex_unlock(&philo->deadischeck);
}

long long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	smart_usleep(int time)
{
	long long int	rules;
	long long int	start;

	rules = (long long int) time;
	start = get_time();
	while (get_time() - start < rules)
		usleep(50);
}
