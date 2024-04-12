/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:19:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 02:01:41 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_routine(t_philo *philo, int philo_n, int *last_meal)
{
	if (philo->dead == 1)
	{
		ft_clear_sem(philo);
		exit(philo_n);
	}
	ft_think(philo, philo_n);
	if (philo->dead == 1)
	{
		ft_clear_sem(philo);
		exit(philo_n);
	}
	sem_wait(philo->prioritie);
	ft_eat(philo, philo_n, philo->fork, last_meal);
	if (philo->dead == 1)
	{
		ft_clear_sem(philo);
		exit(philo_n);
	}
	ft_sleep(philo, philo_n);
	if (philo->dead == 1)
	{
		ft_clear_sem(philo);
		exit(philo_n);
	}
	return (1);
}
