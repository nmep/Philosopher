/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/03 19:33:57 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_print_time(t_philo *philo, int *last_meal)
{
	struct timeval	t;
	long			res;

	gettimeofday(&t, NULL);
	res = (t.tv_sec * 1000 + t.tv_usec * 0.001) - philo->time.time_start;
	if (last_meal)
		*last_meal = (int) res;
	return (res);
}

long	ft_timestamp(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec * 0.001));
}

void	ft_usleep(int elapsed, t_philo *philo)
{
	long	time;

	time = ft_timestamp();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex.print);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex.print);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.print);
		if (ft_timestamp() - time >= elapsed)
			break ;
		usleep(1);
	}
}

inline int	ft_think(t_philo *philo, int philo_n)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	if (philo->dead == 1)
		return (0);
	printf("%ld %d is thinking\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	return (1);
}

inline int ft_sleep(int philo_n, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	if (philo->dead == 1)
		return (0);
	printf("%ld %d is sleeping\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_sleep, philo);
	return (1);
}

inline int ft_eat(t_philo *philo, pthread_mutex_t *first_lock, pthread_mutex_t *second_lock, t_fork_lr *current_pose)
{
	if (!ft_is_dead(philo, current_pose))
		return (0);
	pthread_mutex_lock(first_lock);
	if (!ft_is_dead(philo, current_pose))
		return (pthread_mutex_unlock(first_lock), 0);
	pthread_mutex_lock(second_lock);
	if (!ft_is_dead(philo, current_pose))
		return (pthread_mutex_unlock(first_lock), pthread_mutex_unlock(second_lock), 0);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d has taken a fork\n", ft_print_time(philo, NULL), current_pose->l_fork->fork_n + 1);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is eating\n", ft_print_time(philo, &current_pose->last_meal), current_pose->l_fork->fork_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_eat, philo);
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
	return (1);
}

inline int	ft_is_dead(t_philo *philo, t_fork_lr *current_fork_pose)
{
	long	time_stamp;

	time_stamp = 0;
	pthread_mutex_lock(&philo->mutex.print);
	time_stamp = ((ft_timestamp() - philo->time.time_start) - current_fork_pose->last_meal);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(&philo->mutex.print), 0);
	pthread_mutex_unlock(&philo->mutex.print);
	if (time_stamp >= philo->ph_data.time_to_die)
	{
		pthread_mutex_lock(&philo->mutex.print);
		philo->dead = 1;
		printf("%ld %d died\n", time_stamp, current_fork_pose->l_fork->fork_n + 1);
		pthread_mutex_unlock(&philo->mutex.print);
		return (0);
	}
	return (1);
}
