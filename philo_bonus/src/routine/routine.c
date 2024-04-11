/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:19:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/11 15:49:01 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_routine(t_philo *philo, int philo_n, int *last_meal)
{
	printf("philo %d 1\n", philo_n);
	if (philo->dead == 1)
	{
		sem_close(philo->fork);
		exit(philo_n);
	}
	printf("philo %d 2\n", philo_n);
	ft_think(philo, philo_n);
	if (philo->dead == 1)
	{
		sem_close(philo->fork);
		exit(philo_n);
	}
	printf("philo %d 3\n", philo_n);
	ft_eat(philo, philo_n, philo->fork, last_meal);
	if (philo->dead == 1)
	{
		sem_close(philo->fork);
		exit(philo_n);
	}
	printf("philo %d 4\n", philo_n);
	ft_sleep(philo, philo_n);
	if (philo->dead == 1)
	{
		sem_close(philo->fork);
		exit(philo_n);
	}
	printf("philo %d 5\n", philo_n);
	return (1);
}
