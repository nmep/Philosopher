/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/03 15:48:08 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_philo(t_philo *philo, t_fork_lr *current_fork_pose)
{
	if (!ft_is_dead(philo, current_fork_pose))
		return (0);
	if (!ft_think(philo, current_fork_pose->l_fork->fork_n))
		return (0);
	if (current_fork_pose->l_fork->fork_n == philo->ph_data.p_number - 1)
	{
		if (!ft_eat(philo,&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n] ,
			&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], current_fork_pose))
			return (0);
	}
	else
	{
		if (!ft_eat(philo, &philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], 
			&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose))
			return (0);
	}
	if (!ft_is_dead(philo, current_fork_pose))
		return (0);
	ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	return (1);
}
