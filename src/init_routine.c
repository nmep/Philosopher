/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 13:57:33 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// fonction servant a assigner x et y fourchette a z pihlosopher
void	ft_fork_position_init(t_fork_pos **fork_pos, int position, int nb_philo)
{
	(*fork_pos)[position].l_fork.fork_number = position;
	(*fork_pos)[position].r_fork.fork_number = position - 1;
	if ((*fork_pos)[position].r_fork.fork_number < 0)
		(*fork_pos)[position].r_fork.fork_number = nb_philo - (position + 1);
}

int	ft_init_routine_data(t_philo *philo, t_fork_pos *save_fork_pose)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.p_number)
		ft_fork_position_init(&philo->fork.fork_pos, i, philo->ph_data.p_number); // init fork pose number
	save_fork_pose = philo->fork.fork_pos; // addresse du pointeur de fork pose
	philo->ph = malloc(sizeof(pthread_t) * philo->ph_data.p_number); // malloc tableau thread philo
	if (!philo->ph)
		return (ERROR_MALLOC);
	philo->fork.tab_fork = malloc(sizeof(pthread_mutex_t) * philo->ph_data.p_number); // malloc talbeau de mutex pour chaque fourchette
	if (!philo->fork.tab_fork)
		return (free(philo->ph), ERROR_MALLOC);
	return (1);
}

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->ph_data.p_number) // init mutex
		pthread_mutex_init(&philo->fork.tab_fork[i], NULL);
	pthread_mutex_init(&philo->fork.fork_pos_incr, NULL);
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->fork.fork_pos_addr_incr, NULL);
}

void	ft_clean_routine_data(t_philo *philo, t_fork_pos *save_fork_pose, int *i)
{
	pthread_mutex_destroy(&philo->fork.fork_pos_addr_incr);
	pthread_mutex_destroy(&philo->print);
	pthread_mutex_destroy(&philo->fork.fork_pos_incr);
	while (--(*i) > -1)
		pthread_mutex_destroy(&philo->fork.tab_fork[(*i)]);
	free(philo->ph);
	free(philo->fork.tab_fork);
	free(save_fork_pose);
}

int	ft_init_routine(t_philo *philo)
{
	int				i;
	t_fork_pos		*save_fork_pose;

	save_fork_pose = NULL;
	if (ft_init_routine_data(philo, save_fork_pose) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	ft_init_mutex(philo);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_create(&philo->ph[i], NULL, ft_routine, philo) != 0)
			return (free(philo->ph), free(philo->fork.tab_fork), 0);
		usleep(300);
		pthread_mutex_lock(&philo->print);
		philo->fork.fork_pos++;
		pthread_mutex_unlock(&philo->print);
	}
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		if (pthread_join(philo->ph[i], NULL) != 0)
			return (free(philo->ph), free(philo->fork.tab_fork), 0);
	}
	ft_clean_routine_data(philo, save_fork_pose, &i);
	return (1);
}
