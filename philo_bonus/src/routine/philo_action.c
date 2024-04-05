/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:21:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/06 01:01:05 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_think(t_philo *philo, int philo_n)
{
	printf("%d %d is thinking\n", ft_print_time(philo), philo_n);
	return (1);
}

int	ft_sleep(t_philo *philo, int philo_n)
{
	// dormir;
	printf("%d %d is sleeping\n", ft_print_time(philo), philo_n);
	// zzzzzzzzzzzzzzzzzzzzz
	ft_usleep(philo, philo->ph_data.time_to_sleep);
	// chef waki wake up
	return (1);
}

int	ft_eat(t_philo *philo, int philo_n, sem_t *forks)
{
	// prendre les fourcchette;
	sem_wait(forks);
	sem_wait(forks);
	// manger
	printf("%d %d is eating\n", ft_print_time(philo), philo_n);
	// attendre
	ft_usleep(philo, philo->ph_data.time_to_eat);
	// lache ca on t'a dit gamin
	sem_post(forks);
	sem_post(forks);
	return (1);
}
