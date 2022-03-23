/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:39:58 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 12:01:06 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

static t_bool	str_is_int(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	if (((index == 10 && ft_strncmp(str, "2147483647", 10) <= 0) || index < 10)
		&& ft_atoi(str) >= 1)
		return (TRUE);
	ft_putstr("Arguments must not be greater than the int max or lower than 1.\n");
	return (FALSE);
}

static t_bool	str_is_digit(char *str)
{
	int	index;

	index = 0;
	if (!str[0])
	{
		ft_putstr("An argument is empty.\n");
		return (FALSE);
	}
	while (str[++index])
	{
		if (str[index] < '0' || str[index] > '9')
		{
			ft_putstr("the arguments must only contains digit.\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	parse(int argc, char **argv)
{
	int	index;

	index = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr("There must be 4 or 5 args with the executable.\n");
		return (FALSE);
	}
	while (argv[++index])
	{
		if (!str_is_digit(argv[index]))
			return (FALSE);
		if (!str_is_int(argv[index]))
			return (FALSE);
	}
	if (ft_atoi(argv[1]) > 1024)
	{
		ft_putstr("Cannot have more than 1024 threads.\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	init_info(int argc, char **argv, t_info *info)
{
	int	index;

	index = -1;
	if (!parse(argc, argv))
		return (FALSE);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	info->time_to_start = get_time();
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
