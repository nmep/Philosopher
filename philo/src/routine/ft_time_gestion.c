/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:07:01 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/10 19:18:29 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_print_time(t_philo *philo, int *last_meal)
{
	struct timeval	t;
	long			res;

	gettimeofday(&t, NULL);
	res = (t.tv_sec * 1000 + t.tv_usec * 0.001) - philo->time.time_start;
	pthread_mutex_lock(&philo->mutex.last_meal);
	if (last_meal)
		*last_meal = (int) res;
	pthread_mutex_unlock(&philo->mutex.last_meal);
	return (res);
}

long	ft_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec * 0.001));
}

void	ft_usleep(int elapsed, t_philo *philo)
{
	long	time;

	time = ft_timestamp();
	while (1)
	{
		if (!ft_check_death_philo(philo))
			break ;
		if (ft_timestamp() - time >= elapsed)
			break ;
		usleep(1);
	}
}
