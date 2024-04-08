/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_n_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:06:34 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 17:45:19 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_loop_eat(t_philo *philo, int philo_n, int *last_meal)
{
	int	i;

	i = 0;
	exit (0);
	while (i < philo->ph_data.number_of_time_p_eat)
	{
		ft_routine(philo, philo_n, last_meal);
		i++;
	}
}