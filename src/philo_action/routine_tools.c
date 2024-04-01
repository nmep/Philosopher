/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/01 21:03:18 by lgarfi           ###   ########.fr       */
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

void	ft_usleep(int elapsed)
{
	long	time;

	time = ft_timestamp();
	while (1)
	{
		if (ft_timestamp() - time >= elapsed)
			break ;
		usleep(1);
	}
}

inline void	ft_think(t_philo *philo, int philo_n)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is thinking\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
}

inline void ft_sleep(int philo_n, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is sleeping\n", ft_print_time(philo, NULL), philo_n + 1);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_sleep);
}

inline void ft_eat(t_philo *philo, pthread_mutex_t *first_lock, pthread_mutex_t *second_lock, t_fork_lr *current_pose)
{
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d has taken a fork\n", ft_print_time(philo, NULL), current_pose->l_fork->fork_n + 1);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is eating\n", ft_print_time(philo, &philo->last_meal), current_pose->l_fork->fork_n + 1);
	// printf("philo %d last meal = %d\n",current_pose->l_fork->fork_n, philo->last_meal);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_usleep(philo->ph_data.time_to_eat);
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
}
