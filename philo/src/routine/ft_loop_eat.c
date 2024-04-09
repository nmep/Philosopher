/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:11:48 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/09 21:52:53 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_loop_n_time(t_philo *philo, t_fork_lr *current_fork_pose)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.number_of_time_p_eat)
	{
		pthread_mutex_lock(&philo->mutex.print);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex.print);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.print);
		if (!ft_routine(philo, current_fork_pose))
			break ;
	}
}

void	ft_infinite_loop(t_philo *philo, t_fork_lr *current_fork_pose)
{
	while (true)
	{
		pthread_mutex_lock(&philo->mutex.print);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex.print);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.print);
		if (!ft_routine(philo, current_fork_pose))
			break ;
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
