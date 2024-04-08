/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:21:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 18:07:37 by lgarfi           ###   ########.fr       */
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
	// dormir;
	printf("%d %d is sleeping\n", ft_print_time(philo, NULL), philo_n);
	// zzzzzzzzzzzzzzzzzzzzz
	ft_usleep(philo->ph_data.time_to_sleep);
	// chef waki wake up
	return (1);
}

int	ft_eat(t_philo *philo, int philo_n, sem_t *forks, int *last_meal)
{
	// printf("philo %d a prit une fourchette\n", philo_n);
	sem_wait(forks);
	if (!ft_check_death(philo, last_meal))
	{
		sem_post(forks);
		exit(PHILO_DEATH);
		exit(philo_n);
		exit(philo_n);
	}
	// printf("philo %d a prit une fourchette\n", philo_n);
	sem_wait(forks);
	if (!ft_check_death(philo, last_meal))
	{
		sem_post(forks);
		sem_post(forks);
		exit(philo_n);
	}
	// manger
	printf("%d %d is eating\n", ft_print_time(philo, last_meal), philo_n);
	// attendre
	ft_usleep(philo->ph_data.time_to_eat);
	// lache ca on t'a dit gamin
	sem_post(forks);
	sem_post(forks);
	return (1);
}

bool	ft_check_death(t_philo *philo, int *last_meal)
{
	if (*last_meal - philo->time.start >= philo->ph_data.time_to_die)
		return (false);
	return (true);
}