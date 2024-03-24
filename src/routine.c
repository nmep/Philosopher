// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
// /*                                               J +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/19 20:50:54 by lgarfi            #+#    #+#             */
// /*   Updated: 2024/03/21 18:27:27 by lgarfi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg_philo)
{
	t_philo	*philo;
	t_fork_pos *fork_pose;
	int	left_fork;
	int	right_fork;
	philo = arg_philo; // prendre le parametre du

	pthread_mutex_lock(&philo->fork.fork_pos_incr);
	fork_pose = philo->fork.fork_pos;
	philo->fork.fork_pos++; 
	left_fork = fork_pose->l_fork.fork_number;
	right_fork = fork_pose->r_fork.fork_number;
	pthread_mutex_unlock(&philo->fork.fork_pos_incr);
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->fork.tab_fork[left_fork]);
		pthread_mutex_lock(&philo->fork.tab_fork[right_fork]);
		gettimeofday(&philo->timestamp, NULL);
		printf("%ld philo %d has taken a fork\n", philo->timestamp.tv_usec,
			fork_pose->l_fork.fork_number);
		gettimeofday(&philo->timestamp, NULL);
		printf("%ld philo %d is eating\n", philo->timestamp.tv_usec, fork_pose->l_fork.fork_number);
		usleep(philo->ph_data.time_to_eat);
	}
	else
	{
		pthread_mutex_lock(&philo->fork.tab_fork[right_fork]);
		pthread_mutex_lock(&philo->fork.tab_fork[left_fork]);
		gettimeofday(&philo->timestamp, NULL);
		printf("%ld philo %d has taken a fork\n", philo->timestamp.tv_usec,
			fork_pose->l_fork.fork_number);
		gettimeofday(&philo->timestamp, NULL);
		printf("%ld philo %d is eating\n", philo->timestamp.tv_usec, fork_pose->l_fork.fork_number);
		usleep(philo->ph_data.time_to_eat);
	}
	pthread_mutex_unlock(&philo->fork.tab_fork[left_fork]);
	pthread_mutex_unlock(&philo->fork.tab_fork[right_fork]);
	

	return (NULL);
}
