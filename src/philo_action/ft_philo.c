/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/30 17:27:09 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo(t_philo *philo, t_fork_lr *current_fork_pose)
{
	ft_think(philo, current_fork_pose->l_fork->fork_n);
	if (current_fork_pose->l_fork->fork_n < current_fork_pose->r_fork->fork_n)
	{
		ft_eat(philo, &philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
			&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], current_fork_pose);
		ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	}
	else
	{
		ft_eat(philo, &philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
				&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose);
		ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	}
	return (1);
}
