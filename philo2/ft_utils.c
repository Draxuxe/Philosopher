/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:26:57 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 16:51:34 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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

void	ft_put_message(t_philosopher *philo, int message)
{
	int	actu_time;

	pthread_mutex_lock(&philo->deadischeck);
	pthread_mutex_lock(philo->info.writter);
	if (philo->dead == FALSE)
	{	
		actu_time = ft_time() - philo->info.time_to_start;
		ft_putnbr(actu_time);
		ft_putstr(" ms philo numero ");
		ft_putnbr(philo->id);
		if (message == THINK)
			ft_putstr(" is thinking\n");
		else if (message == SLEEP)
			ft_putstr(" is sleeping\n");
		else if (message == FORK)
			ft_putstr(" has taken a fork\n");
		else if (message == EAT)
			ft_putstr(" is eating\n");
		else if (message == DIE)
			ft_putstr(" died\n");
	}
	pthread_mutex_unlock(philo->info.writter);
	pthread_mutex_unlock(&philo->deadischeck);
}

long long int	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_smart_usleep(int time)
{
	long long int	rules;
	long long int	start;

	rules = (long long int) time;
	start = ft_time();
	while (ft_time() - start < rules)
		usleep(50);
}
