/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/01 19:19:47 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_philo(t_philo *philo, t_fork_lr *current_fork_pose)
{
	ft_think(philo, current_fork_pose->l_fork->fork_n);
	if (current_fork_pose->l_fork->fork_n % 2 == 0)
	{
		ft_eat(philo,&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n] ,
			&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose);
	}
	else
	{
		ft_eat(philo, &philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], 
		&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose);
	}
	ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	return (1);
}
