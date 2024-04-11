/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:30:27 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/11 15:42:18 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_time_milli(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

int	ft_print_time(t_philo *philo, int *last_meal)
{
	int	timestamp;

	timestamp = ft_get_time_milli() - philo->time.start;
	if (!last_meal)
		return (timestamp);
	*last_meal = timestamp;
	return (timestamp);
}

int	ft_usleep(int time_to_wait, t_philo *philo)
{
	long	time_atm;

	time_atm = ft_get_time_milli();
	while (ft_get_time_milli() - time_atm <= time_to_wait 
			&& philo->dead == 0)
		usleep(1);
	if (philo->dead == 1)
		exit(philo->id);
	return (1);
}
