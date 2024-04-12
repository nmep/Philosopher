/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:26:54 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 03:33:42 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_death(void *arg_philo)
{
	t_philo	*philo;
	long	timestamp;

	philo = arg_philo;
	philo->die = sem_open("/die", O_CREAT, 0644, 1);
	while (philo->eat_finish != 1)
	{
		timestamp = ft_print_time(philo, NULL);
		if (philo->last_meal * 2 < philo->ph_data.time_to_eat
			&& philo->ph_data.p_number > 1)
			continue ;
		if (timestamp - philo->last_meal >= philo->ph_data.time_to_die)
		{
			philo->dead = 1;
			sem_wait(philo->die);
			printf("%ld %d died\n", timestamp, philo->id);
			ft_clear_sem(philo);
			exit (philo->id);
		}
	}
	sem_close(philo->die);
	return (0);
}
