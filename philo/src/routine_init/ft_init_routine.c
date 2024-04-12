/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 04:42:41 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_routine_data(t_philo *philo, t_fork_lr **save_fork_pose)
{
	philo->dead = 0;
	if (ft_fork_position_init(philo, save_fork_pose) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	philo->ph = malloc(sizeof(pthread_t) * philo->ph_data.p_number);
	if (!philo->ph)
		return (free(philo->f_data.ph_fork_pos), ERROR_MALLOC);
	philo->mutex.tab_fork = \
		malloc(sizeof(pthread_mutex_t) * philo->ph_data.p_number);
	if (!philo->mutex.tab_fork)
		return (free(philo->ph), free(philo->f_data.ph_fork_pos), ERROR_MALLOC);
	return (1);
}

int	ft_init_routine(t_philo *philo)
{
	int				i;
	t_fork_lr		*save_fork_pose;

	save_fork_pose = NULL;
	philo->finish = 0;
	if (ft_init_routine_data(philo, &save_fork_pose) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	ft_init_mutex(philo);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_create(&philo->ph[i], NULL, ft_loop_eat_n_time, philo) != 0)
			return (ft_clean_thread(philo, i), \
				ft_clean_routine_data(philo, save_fork_pose, &i), 0);
	}
	i = -1;
	ft_check_death(philo, save_fork_pose);
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_join(philo->ph[i], NULL) != 0)
			return (free(philo->ph), free(philo->f_data.fork_pos_state), 0);
	}
	ft_clean_routine_data(philo, save_fork_pose, &i);
	return (1);
}
