/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:21:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/09 17:05:41 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_think(t_philo *philo, int philo_n)
{
	printf("%d %d is thinking\n", ft_print_time(philo, NULL), philo_n);
	return (1);
}

inline int	ft_sleep(t_philo *philo, int philo_n, int *last_meal)
{
	printf("%d %d is sleeping\n", ft_print_time(philo, NULL), philo_n);
	ft_usleep(philo->ph_data.time_to_sleep, last_meal, philo);
	return (1);
}

int	ft_eat(t_philo *philo, int philo_n, sem_t *forks, int *last_meal)
{
	if (!ft_check_death(philo, last_meal))
	{
		sem_post(forks);
		exit(philo_n);
	}
	sem_wait(forks);
	printf("%d %d has taken a fork\n", ft_print_time(philo, NULL), philo_n);
	if (!ft_check_death(philo, last_meal))
	{
		sem_post(forks);
		exit(philo_n);
	}
	sem_wait(forks);
	printf("%d %d has taken a fork\n", ft_print_time(philo, NULL), philo_n);
	if (!ft_check_death(philo, last_meal))
	{
		sem_post(forks);
		sem_post(forks);
		exit(philo_n);
	}
	printf("%d %d is eating\n", ft_print_time(philo, last_meal), philo_n);
	ft_usleep(philo->ph_data.time_to_eat, last_meal, philo);
	sem_post(forks);
	sem_post(forks);
	return (1);
}

bool	ft_check_death(t_philo *philo, int *last_meal)
{
	int	timestamp;

	if (!last_meal)
		return (true);
	timestamp = ft_print_time(philo, NULL) - *last_meal;
	if (timestamp + 1 >= philo->ph_data.time_to_die
		&& *last_meal >= philo->ph_data.time_to_eat)
		return (false);
	return (true);
}
