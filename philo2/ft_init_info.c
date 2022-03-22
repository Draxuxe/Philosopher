/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:39:58 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/18 17:25:06 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && (str1[i] || str2[i]) && --n)
		i++;
	return ((unsigned char) str1[i] - str2[i]);
}

t_bool	ft_str_is_int(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	if (((index == 10 && ft_strncmp(str, "2147483647", 10) <= 0) || index < 10)
		&& ft_atoi(str) >= 1)
		return (TRUE);
	ft_putstr("Un argument est superieur au int max ou inferieur à 1.\n");
	return (FALSE);
}

t_bool	ft_str_is_digit(char *str)
{
	int	index;

	index = 0;
	if (!str[0])
	{
		ft_putstr("Un argument est vide.\n");
		return (FALSE);
	}
	while (str[++index])
	{
		if (str[index] < '0' || str[index] > '9')
		{
			ft_putstr("Un argument n'est pas uniquement un digital.\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	ft_parse(int argc, char **argv)
{
	int	index;

	index = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr("Nombre d'arguement incorrect.\n");
		return (FALSE);
	}
	while (argv[++index])
	{
		if (!ft_str_is_digit(argv[index]))
			return (FALSE);
		if (!ft_str_is_int(argv[index]))
			return (FALSE);
	}
	if (ft_atoi(argv[1]) > 1024)
	{
		ft_putstr("Il ne peut avoir plus de 1024 philosophers. \n");
		return (FALSE);
	}
	if (ft_atoi(argv[1]) == 1)
		return (FALSE);
	return (TRUE);
}

t_bool	ft_init_info(int argc, char **argv, t_info *info)
{
	int	index;

	index = -1;
	if (!ft_parse(argc, argv))
		return (FALSE);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	info->time_to_start = ft_time();
	info->writter = malloc(sizeof(pthread_mutex_t));
	if (!info->writter)
		return (FALSE);
	pthread_mutex_init(info->writter, NULL);
	info->forks = malloc(sizeof(pthread_mutex_t)
			* info->number_of_philosophers);
	if (!info->forks)
		return (FALSE);
	while (++index < info->number_of_philosophers)
		pthread_mutex_init(&info->forks[index], NULL);
	return (TRUE);
}
