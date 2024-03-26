/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:44:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 10:26:28 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// faire incrementer l'addresse du tableau des position de fourchette et 
// garder l'adresse contenant les position des fourchettes gauche et droite
// du thread actuel
inline void	ft_init_fork_data(t_philo *philo, t_fork_pos *fork_pose)
{
	pthread_mutex_lock(&philo->fork.fork_pos_incr);
	fork_pose = philo->fork.fork_pos;
	philo->fork.fork_pos++;
	pthread_mutex_unlock(&philo->fork.fork_pos_incr);
}

// return 0 si la condition est fausse
// return 1 si la condition est true
inline int	ft_check_fork(t_fork_pos *fork_pose)
{
	return (fork_pose->l_fork.state == 0 && fork_pose->r_fork.state == 0);
}

inline void	ft_think(int philo_n, t_philo *philo)
{
	gettimeofday(&philo->timestamp, NULL);
	pthread_mutex_lock(&philo->print);
	printf("%ld philo %d is thinking\n", philo->timestamp.tv_usec, philo_n);
	pthread_mutex_unlock(&philo->print);
	usleep(200); // verifier le temps a mettre pour think;
}

inline void ft_sleep(int philo_n, t_philo *philo)
{
	gettimeofday(&philo->timestamp, NULL);
	pthread_mutex_lock(&philo->print);
	printf("%ld philo %d is sleeping\n", philo->timestamp.tv_usec, philo_n);
	pthread_mutex_unlock(&philo->print);
}

inline void	ft_get_fork(pthread_mutex_t first_lock, pthread_mutex_t second_lock)
{
	pthread_
}
