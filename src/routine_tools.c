/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/28 13:51:55 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// return 0 si la condition est fausse
// return 1 si la condition est true
inline int	ft_check_fork(t_fork_lr *fork_pose, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.f_state);
	if (philo->f_data.fork_pos_state[fork_pose->l_fork->fork_n].state == 0 
		&& philo->f_data.fork_pos_state[fork_pose->r_fork->fork_n].state == 0)
		return (pthread_mutex_unlock(&philo->mutex.f_state), 1);
	return (pthread_mutex_unlock(&philo->mutex.f_state), 0);
}

inline void	ft_think(t_philo *philo, int philo_n)
{
	// pthread_mutex_lock(&philo->mutex.time);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld philo %d is thinking\n", philo->time.timestamp.tv_usec, philo_n);
	// pthread_mutex_unlock(&philo->mutex.time);
	pthread_mutex_unlock(&philo->mutex.print);
	usleep(200); // verifier le temps a mettre pour think;
}

inline void ft_sleep(int philo_n, t_philo *philo)
{
	// pthread_mutex_lock(&philo->mutex.time);
	pthread_mutex_lock(&philo->mutex.print);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld philo %d is sleeping\n", philo->time.timestamp.tv_usec, philo_n);
	// pthread_mutex_unlock(&philo->mutex.time);
	pthread_mutex_unlock(&philo->mutex.print);
	usleep(philo->ph_data.time_to_sleep);
}

inline	void ft_eat(t_philo *philo, pthread_mutex_t first_lock, pthread_mutex_t second_lock, t_fork_lr *current_pose)
{
	pthread_mutex_lock(&first_lock);
	pthread_mutex_lock(&second_lock);
	pthread_mutex_lock(&philo->mutex.f_state);
	current_pose->l_fork->state = 1;
	current_pose->r_fork->state = 1;
	pthread_mutex_unlock(&philo->mutex.f_state);
	pthread_mutex_lock(&philo->mutex.print);
	pthread_mutex_lock(&philo->mutex.time);
	gettimeofday(&philo->time.timestamp, NULL);
	printf("%ld philo %d has eaten\n", philo->time.timestamp.tv_usec, current_pose->l_fork->fork_n);
	pthread_mutex_unlock(&philo->mutex.time);
	pthread_mutex_unlock(&philo->mutex.print);
	usleep(philo->ph_data.time_to_eat);
	current_pose->hungry = 1;
	pthread_mutex_lock(&philo->mutex.f_state);
	current_pose->l_fork->state = 0;
	current_pose->r_fork->state = 0;
	pthread_mutex_unlock(&philo->mutex.f_state);
	pthread_mutex_unlock(&second_lock);
	pthread_mutex_unlock(&first_lock);
}
