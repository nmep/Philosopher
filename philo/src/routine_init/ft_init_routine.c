/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/10 19:33:35 by lgarfi           ###   ########.fr       */
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

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.p_number)
		pthread_mutex_init(&philo->mutex.tab_fork[i], NULL);
	pthread_mutex_init(&philo->mutex.print, NULL);
	pthread_mutex_init(&philo->mutex.f_pos_addr_incr, NULL);
	pthread_mutex_init(&philo->mutex.death, NULL);
	pthread_mutex_init(&philo->mutex.last_meal, NULL);
	pthread_mutex_init(&philo->mutex.eat_finish, NULL);
}

void	ft_clean_routine_data(t_philo *philo, t_fork_lr *save_fork_pose, int *i)
{
	pthread_mutex_destroy(&philo->mutex.eat_finish);
	pthread_mutex_destroy(&philo->mutex.last_meal);
	pthread_mutex_destroy(&philo->mutex.death);
	pthread_mutex_destroy(&philo->mutex.f_pos_addr_incr);
	pthread_mutex_destroy(&philo->mutex.print);
	while (--(*i) > -1)
		pthread_mutex_destroy(&philo->mutex.tab_fork[(*i)]);
	free(philo->ph);
	free(philo->mutex.tab_fork);
	free(save_fork_pose);
}

void	*ft_check_death(t_philo *arg_philo, t_fork_lr *save_fork_pose)
{
	t_philo	*philo;
	int		i;
	long	timestamp;

	philo = arg_philo;
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
		while (++i < philo->ph_data.p_number)
		{
			pthread_mutex_lock(&philo->mutex.last_meal);
			if (save_fork_pose[i].last_meal * 2 < philo->ph_data.time_to_eat && philo->ph_data.p_number > 1)
			{
				pthread_mutex_unlock(&philo->mutex.last_meal);
				continue ;
			}
			timestamp -= save_fork_pose[i].last_meal;
			pthread_mutex_unlock(&philo->mutex.last_meal);
			if (timestamp >= philo->ph_data.time_to_die)
			{
				pthread_mutex_lock(&philo->mutex.death);
				philo->dead = 1;
				pthread_mutex_unlock(&philo->mutex.death);
				pthread_mutex_lock(&philo->mutex.print);
				printf("%ld %d died\n", ft_print_time(philo, NULL), i);
				pthread_mutex_unlock(&philo->mutex.print);
				pthread_mutex_lock(&philo->mutex.death);
				pthread_mutex_unlock(&philo->mutex.death);
				break ;
			}
		}
		usleep(philo->ph_data.time_to_eat * 0.5);
	}
	return (NULL);
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
