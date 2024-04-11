/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_n_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:06:34 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/11 15:38:26 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_loop_eat(t_philo *philo, int philo_n, int *last_meal, int *pid_tab)
{
	int	i;

	i = -1;
	if (philo->ph_data.p_number % 2 == 0)
	{
		if (philo_n % 2 != 0)
			ft_usleep(philo->ph_data.time_to_eat, philo);
	}
	else if (philo->ph_data.p_number % 2 != 0)
	{
		if (philo_n % 2 == 0)
			ft_usleep(philo->ph_data.time_to_eat, philo);
	}
	if (philo->ph_data.number_of_time_p_eat == -1)
	{
		while (true)
			ft_routine(philo, philo_n, last_meal);
	}
	else
	{
		while (i++ < philo->ph_data.number_of_time_p_eat)
			ft_routine(philo, philo_n, last_meal);
	}
	philo->eat_finish = 1;
	// free(pid_tab);
	(void)pid_tab;
	sem_close(philo->fork);
	exit (0);
}
