/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:07:15 by aleferra          #+#    #+#             */
/*   Updated: 2022/03/23 12:09:03 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	t_philosopher	*philo;

	philo = NULL;
	if (!init_info(argc, argv, &info))
		return (0);
	init_philo(&philo, info);
	launcher(philo);
	clear_info(&info);
	clear_philo(&philo);
	return (0);
}
