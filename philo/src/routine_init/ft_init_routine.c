/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 22:31:16 by garfi            ###   ########.fr       */
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

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.p_number)
		pthread_mutex_init(&philo->mutex.tab_fork[i], NULL);
	pthread_mutex_init(&philo->mutex.print, NULL);
	pthread_mutex_init(&philo->mutex.f_pos_addr_incr, NULL);
	pthread_mutex_init(&philo->mutex.death, NULL);
}

void	ft_clean_thread(t_philo *philo, int i)
{
	int	index;

	index = 0;
	while (index < i)
	{
		if (pthread_join(philo->ph[index], NULL) != 0)
			return ;
		index++;
	}
}

void	ft_clean_routine_data(t_philo *philo, t_fork_lr *save_fork_pose, int *i)
{
	pthread_mutex_destroy(&philo->mutex.death);
	pthread_mutex_destroy(&philo->mutex.f_pos_addr_incr);
	pthread_mutex_destroy(&philo->mutex.print);
	while (--(*i) > -1)
		pthread_mutex_destroy(&philo->mutex.tab_fork[(*i)]);
	free(philo->ph);
	free(philo->mutex.tab_fork);
	free(save_fork_pose);
}

int	ft_init_routine(t_philo *philo)
{
	int				i;
	t_fork_lr		*save_fork_pose;

	save_fork_pose = NULL;
	if (ft_init_routine_data(philo, &save_fork_pose) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	ft_init_mutex(philo);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_create(&philo->ph[i], NULL, ft_loop_eat_n_time, philo) != 0)
			return (ft_clean_thread(philo, i), \
				ft_clean_routine_data(philo, save_fork_pose, &i), \
				0);
	}
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_join(philo->ph[i], NULL) != 0)
			return (free(philo->ph), free(philo->f_data.fork_pos_state), 0);
	}
	ft_clean_routine_data(philo, save_fork_pose, &i);
	return (1);
}
