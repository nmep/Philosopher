/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:11:48 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/10 19:30:48 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_loop_n_time(t_philo *philo, t_fork_lr *current_fork_pose)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.number_of_time_p_eat)
	{
		if (!ft_check_death_philo(philo))
			break ;
		if (!ft_routine(philo, current_fork_pose))
			break ;
	}
	pthread_mutex_lock(&philo->mutex.eat_finish);
	philo->finish = 1;
	pthread_mutex_unlock(&philo->mutex.eat_finish);
}

void	ft_infinite_loop(t_philo *philo, t_fork_lr *current_fork_pose)
{
	while (true)
	{
		pthread_mutex_lock(&philo->mutex.death);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex.death);
			{
				pthread_mutex_lock(&philo->mutex.eat_finish);
				philo->finish = 1;
				pthread_mutex_unlock(&philo->mutex.eat_finish);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->mutex.death);
		if (!ft_routine(philo, current_fork_pose))
		{
			pthread_mutex_lock(&philo->mutex.eat_finish);
			philo->finish = 1;
			pthread_mutex_unlock(&philo->mutex.eat_finish);
			break ;
		}
	}
}

void	*ft_loop_eat_n_time(void *arg_philo)
{
	t_philo		*philo;
	t_fork_lr	*current_fork_pose;

	current_fork_pose = NULL;
	philo = arg_philo;
	pthread_mutex_lock(&philo->mutex.f_pos_addr_incr);
	current_fork_pose = philo->f_data.ph_fork_pos;
	philo->f_data.ph_fork_pos++;
	pthread_mutex_unlock(&philo->mutex.f_pos_addr_incr);
	if (philo->ph_data.number_of_time_p_eat == -1)
		ft_infinite_loop(philo, current_fork_pose);
	else
		ft_loop_n_time(philo, current_fork_pose);
	return (NULL);
}
