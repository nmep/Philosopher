/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:30:27 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 17:07:58 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_time_milli()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

int	ft_print_time(t_philo *philo)
{
	return (ft_get_time_milli() - philo->time.start);
}

int	ft_usleep(int time_to_wait)
{
	long	time_atm;

	time_atm = ft_get_time_milli();
	while (ft_get_time_milli() - time_atm <= time_to_wait)
	{
		usleep(1);
	}
	return (1);
}
