/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:50:54 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 17:41:25 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg_philo)
{
	t_philo	*philo;

	philo = arg_philo;

	pthread_mutex_lock(&philo->fork[philo->ph_data.p_position]);
	pthread_mutex_lock(&philo->fork[philo->ph_data.r_fork]);
	printf("fork g = %d | fork r = %d\n", philo->fork[philo.]);
	write(1, "bonsoir paris\n", 14);
	pthread_mutex_unlock(&philo->fork[philo->ph_data.p_position]);
	pthread_mutex_unlock(&philo->fork[philo->ph_data.r_fork]);
	return (NULL);
}
