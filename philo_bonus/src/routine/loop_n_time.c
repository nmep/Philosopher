/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_n_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:06:34 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/09 16:03:43 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_loop_eat(t_philo *philo, int philo_n, int *last_meal)
{
	int	i;

	i = 0;
	if (philo->ph_data.p_number % 2 == 0)
	{
		if (philo_n % 2 != 0)
			ft_usleep(philo->ph_data.time_to_eat, NULL, philo);
	}
	else
	{
		if (philo_n % 2 == 0)
			ft_usleep(philo->ph_data.time_to_eat, NULL, philo);
	}
	if (philo->ph_data.number_of_time_p_eat == -1)
	{
		while (true)
		{
			if (!ft_check_death(philo, last_meal))
				exit(philo_n);
			ft_routine(philo, philo_n, last_meal);
		}
	}
	else
	{
		while (i < philo->ph_data.number_of_time_p_eat)
		{
			ft_routine(philo, philo_n, last_meal);
			i++;
		}
	}
	exit (0);
}
