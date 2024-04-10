/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/10 19:16:18 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_think(t_philo *philo, int philo_n)
{
	if (!ft_check_death_philo(philo))
		return (0);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is thinking\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	return (1);
}

inline int	ft_sleep(int philo_n, t_philo *philo)
{
	gettimeofday(&philo->time.timestamp, NULL);
	if (!ft_check_death_philo(philo))
		return (0);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%ld %d is sleeping\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_sleep, philo);
	return (1);
}

inline int	ft_eat(t_philo *philo, \
	pthread_mutex_t *first_lock, \
	pthread_mutex_t *second_lock, \
	t_fork_lr *current_pose)
{
	if (!ft_check_death_philo(philo))
		return (0);
	pthread_mutex_lock(first_lock);
	if (!ft_check_death_philo(philo))
		return (pthread_mutex_unlock(first_lock), 0);
	if (second_lock == NULL)
		return (pthread_mutex_unlock(first_lock), 0);
	pthread_mutex_lock(second_lock);
	if (!ft_check_death_philo(philo))
		return (pthread_mutex_unlock(first_lock), \
		pthread_mutex_unlock(second_lock), 0);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d has taken a fork\n", \
		ft_print_time(philo, NULL), \
		current_pose->l_fork->fork_n + 1);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is eating\n", ft_print_time(philo,
			&current_pose->last_meal),
		current_pose->l_fork->fork_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_eat, philo);
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
	return (1);
}

int	ft_check_death_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.death);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(&philo->mutex.death), 0);
	else
		return (pthread_mutex_unlock(&philo->mutex.death), 1);
	pthread_mutex_unlock(&philo->mutex.death);
}
