/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 17:31:44 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork_number_init(t_philo *philo, int position)
{
	philo->ph_data.p_position = position;
	philo->ph_data.r_fork = philo->ph_data.p_position - 1;
	if (philo->ph_data.r_fork < 0)
		philo->ph_data.r_fork = philo->ph_data.p_number - (philo->ph_data.p_position + 1);
}

int	ft_init_thread(t_philo *philo)
{
	int	i;
	int	j;

	philo->ph = malloc(sizeof(pthread_t) * philo->ph_data.p_number);
	if (!philo->ph)
		return (ERROR_MALLOC);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->ph_data.p_number);
	if (!philo->fork)
		return (free(philo->ph), ERROR_MALLOC);
	i = -1;
	while (++i < philo->ph_data.p_number) // init mutex
		pthread_mutex_init(&philo->fork[i], NULL);
	i = -1;
	while (++i < philo->ph_data.p_number)
			ft_fork_number_init(philo, i);
	i = -1;
	while (++i < philo->ph_data.number_of_time_p_eat) //init threads
	{
		j = -1;
		while (++j < philo->ph_data.p_number)
		{
			if (pthread_create(&philo->ph[j], NULL, ft_routine, philo) != 0)
				return (free(philo->ph), free(philo->fork), 0);
			usleep(300);
		}
		j = -1;
		while (++j < philo->ph_data.p_number)
		{
			if (pthread_join(philo->ph[j], NULL) != 0)
				return (free(philo->ph), free(philo->fork), 0);
		}
	}
	while (--i > -1)
		pthread_mutex_destroy(&philo->fork[i]);
	free(philo->ph);
	free(philo->fork);
	return (1);
}
