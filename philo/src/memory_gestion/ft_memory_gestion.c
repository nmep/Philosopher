/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 04:42:09 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 04:42:44 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
