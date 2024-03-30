/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/30 21:04:00 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_to_usleep, struct timeval start, struct timeval end)
{
	long int elapsed;

	elapsed = time_to_usleep - (((end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_usec - start.tv_usec)));
	printf("tw = %ld\n", elapsed);
	usleep(elapsed);
}

void	ft_think(t_philo *philo, int philo_n)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is thinking\n", philo->time.timestamp.tv_usec, philo_n);
	pthread_mutex_unlock(&philo->mutex.print);
}

void ft_sleep(int philo_n, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.start, NULL);
	gettimeofday(&philo->time.timestamp, NULL);
	philo->time.micro_time = philo->time.timestamp.tv_usec;
	printf("%ld %d is sleeping\n", philo->time.timestamp.tv_usec, philo_n);
	pthread_mutex_unlock(&philo->mutex.print);
	// usleep(philo->ph_data.time_to_sleep);
	gettimeofday(&philo->time.end, NULL);
	ft_usleep(philo->ph_data.time_to_sleep, philo->time.start, philo->time.end);
}

void ft_eat(t_philo *philo, pthread_mutex_t *first_lock, pthread_mutex_t *second_lock, t_fork_lr *current_pose)
{
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.start, NULL);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d has taken a fork\n", philo->time.timestamp.tv_usec, current_pose->l_fork->fork_n);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld %d is eating\n", philo->time.timestamp.tv_usec, current_pose->l_fork->fork_n);
	pthread_mutex_unlock(&philo->mutex.print);
	gettimeofday(&philo->time.end, NULL);
	ft_usleep(philo->ph_data.time_to_eat, philo->time.start, philo->time.end);
	pthread_mutex_unlock(first_lock);
	pthread_mutex_unlock(second_lock);
}

// prendre le temps en milli seconde
// le convertir en micro seconde
// le comparer avec time to die
// si le resulat est positif alors c'est bon
// sinon le philo est considere comme mort