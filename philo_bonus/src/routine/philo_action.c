/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:21:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/11 15:54:48 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_think(t_philo *philo, int philo_n)
{
	printf("%d %d is thinking\n", ft_print_time(philo, NULL), philo_n);
	return (1);
}

int	ft_sleep(t_philo *philo, int philo_n)
{
	if (philo->dead == 1)
	{
		exit(philo_n);
	}
	printf("%d %d is sleeping\n", ft_print_time(philo, NULL), philo_n);
	ft_usleep(philo->ph_data.time_to_sleep, philo);
	return (1);
}

int	ft_eat(t_philo *philo, int philo_n, sem_t *forks, int *last_meal)
{
	if (philo->dead == 1)
	{
		sem_close(philo->fork);
		exit(philo_n);
	}
	sem_wait(forks);
	printf("%d %d has taken a fork\n", ft_print_time(philo, NULL), philo_n);
	if (philo->dead == 1)
	{
		sem_post(forks);
		sem_close(philo->fork);
		exit(philo_n);
	}
	if (philo->ph_data.p_number == 1)
	{
		sem_post(forks);
		return (1);
	}
	sem_wait(forks);
	printf("%d %d has taken a fork\n", ft_print_time(philo, NULL), philo_n);
	if (philo->dead == 1)
	{
		sem_post(forks);
		sem_post(forks);
		sem_close(philo->fork);
		exit(philo_n);
	}
	printf("%d %d is eating\n", ft_print_time(philo, last_meal), philo_n);
	ft_usleep(philo->ph_data.time_to_eat, philo);
	sem_post(forks);
	sem_post(forks);
	return (1);
}
