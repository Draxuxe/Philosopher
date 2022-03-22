/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:07:15 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/22 16:28:20 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	t_philosopher	*philo;

	philo = NULL;
	if (!ft_init_info(argc, argv, &info))
		return (0);
	ft_init_philo(&philo, info);
	ft_launcher(philo);
	ft_clear_info(&info);
	ft_clear_philo(&philo);
	return (0);
}
