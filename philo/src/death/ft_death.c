/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 04:40:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 04:41:22 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_death_2(t_philo *philo, long *timestamp, \
	t_fork_lr *save_fork_pose, int *i)
{
	while (++(*i) < philo->ph_data.p_number)
	{
		pthread_mutex_lock(&philo->mutex.last_meal);
		if (save_fork_pose[(*i)].last_meal * 2 < philo->ph_data.time_to_eat
			&& philo->ph_data.p_number > 1)
		{
			pthread_mutex_unlock(&philo->mutex.last_meal);
			continue ;
		}
		*timestamp -= save_fork_pose[(*i)].last_meal;
		pthread_mutex_unlock(&philo->mutex.last_meal);
		if (*timestamp >= philo->ph_data.time_to_die)
		{
			pthread_mutex_lock(&philo->mutex.death);
			philo->dead = 1;
			pthread_mutex_unlock(&philo->mutex.death);
			pthread_mutex_lock(&philo->mutex.print);
			printf("%ld %d died\n", ft_print_time(philo, NULL), *i);
			pthread_mutex_unlock(&philo->mutex.print);
			pthread_mutex_lock(&philo->mutex.death);
			pthread_mutex_unlock(&philo->mutex.death);
			break ;
		}
	}
}

void	*ft_check_death(t_philo *philo, t_fork_lr *save_fork_pose)
{
	int		i;
	long	timestamp;

	while (1)
	{
		pthread_mutex_lock(&philo->mutex.eat_finish);
		if (philo->finish == 1)
		{
			pthread_mutex_unlock(&philo->mutex.eat_finish);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.eat_finish);
		pthread_mutex_lock(&philo->mutex.death);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex.death);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.death);
		i = -1;
		timestamp = ft_print_time(philo, NULL);
		ft_check_death_2(philo, &timestamp, save_fork_pose, &i);
		usleep(philo->ph_data.time_to_eat * 0.5);
	}
	return (NULL);
}
