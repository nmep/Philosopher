/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:19:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 18:07:35 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_routine(t_philo *philo, int philo_n, int *last_meal)
{
	if (!ft_check_death(philo, last_meal))
		exit(PHILO_DEATH);
	ft_think(philo, philo_n);
	if (!ft_check_death(philo, last_meal))
		exit(PHILO_DEATH);
	ft_eat(philo, philo_n, philo->fork, last_meal);
	if (!ft_check_death(philo, last_meal))
		exit(PHILO_DEATH);
	ft_sleep(philo, philo_n);
	if (!ft_check_death(philo, last_meal))
		exit(PHILO_DEATH);
	return (1);
}
