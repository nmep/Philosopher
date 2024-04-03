/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/03 19:37:51 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_fork(t_philo *philo, int i)
{
	philo->f_data.ph_fork_pos[i].l_fork = &philo->f_data.fork_pos_state[i];
	if ((i - 1) < 0)
	{
		philo->f_data.ph_fork_pos[i].r_fork = &philo->f_data.fork_pos_state[(philo->ph_data.p_number - (i + 1))];
	}
	else
		philo->f_data.ph_fork_pos[i].r_fork = &philo->f_data.fork_pos_state[i - 1];
	philo->f_data.ph_fork_pos[i].last_meal = 0;
}

// fonction servant a assigner x et y fourchette a z pihlosopher
int	ft_fork_position_init(t_philo *philo, t_fork_lr **save_fork_pose)
{
	int	i;

	philo->f_data.ph_fork_pos = malloc(sizeof(t_fork_lr) * philo->ph_data.p_number);
	printf("addr de ph fork pos a la creation %p\n", philo->f_data.ph_fork_pos);
	if (!philo->f_data.ph_fork_pos)
		return (ERROR_MALLOC);
	*save_fork_pose = philo->f_data.ph_fork_pos;
	i = -1;
	while (++i < philo->ph_data.p_number)
		ft_get_fork(philo, i);
	return (1);
}

int	ft_init_routine_data(t_philo *philo, t_fork_lr **save_fork_pose)
{
	int	i;

	i = -1;
	philo->dead = 0;
	if (ft_fork_position_init(philo, save_fork_pose) == ERROR_MALLOC) // init fork pose number
		return (ERROR_MALLOC);
	philo->ph = malloc(sizeof(pthread_t) * philo->ph_data.p_number); // malloc tableau thread philo
	if (!philo->ph)
		return (free(philo->f_data.ph_fork_pos), ERROR_MALLOC);
	philo->mutex.tab_fork = malloc(sizeof(pthread_mutex_t) * philo->ph_data.p_number); // malloc talbeau de mutex pour chaque fourchette
	if (!philo->mutex.tab_fork)
		return (free(philo->ph), free(philo->f_data.ph_fork_pos), ERROR_MALLOC);
	return (1);
}

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.p_number) // init mutex
		pthread_mutex_init(&philo->mutex.tab_fork[i], NULL);
	pthread_mutex_init(&philo->mutex.print, NULL);
	pthread_mutex_init(&philo->mutex.f_pos_addr_incr, NULL);
	pthread_mutex_init(&philo->mutex.death, NULL);
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
	printf("addr de ph fork pos avant les threads %p\n", philo->f_data.ph_fork_pos);
	printf("addr de save fork pose a la fin %p\n", &save_fork_pose);
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_create(&philo->ph[i], NULL, ft_routine, philo) != 0)
			return (free(philo->f_data.fork_pos_state), 0);
	}
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_join(philo->ph[i], NULL) != 0)
			return (free(philo->ph), free(philo->f_data.fork_pos_state), 0);
	}
	printf("addr de ph fork pos a la fin %p\n", philo->f_data.ph_fork_pos);
	printf("addr de save fork pose a la fin %p\n", &save_fork_pose);
	ft_clean_routine_data(philo, save_fork_pose, &i);
	return (1);
}
