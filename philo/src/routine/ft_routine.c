/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/09 22:17:30 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	ft_one_philo_eat(t_philo *philo, \
		t_fork_lr *current_fork_pose)
{
	ft_eat(philo,
		&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
		NULL,
		current_fork_pose);
}

inline int	ft_last_philo_eat(t_philo *philo, t_fork_lr *current_fork_pose)
{
	if (!ft_eat(philo,
			&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
			&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
			current_fork_pose))
		return (0);
	return (1);
}

inline int	ft_routine(t_philo *philo, t_fork_lr *current_fork_pose)
{
	if (!ft_think(philo, current_fork_pose->l_fork->fork_n, current_fork_pose))
		return (0);
	if (philo->ph_data.p_number == 1)
		ft_one_philo_eat(philo, current_fork_pose);	
	else if (philo->ph_data.p_number % 2 == 0)
	{
		if ((current_fork_pose->l_fork->fork_n) % 2 == 0)
		{
			if (!ft_last_philo_eat(philo, current_fork_pose))
				return (0);
		}
		else
		{
			if (!ft_eat(philo,
					&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
					&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
					current_fork_pose))
				return (0);
		}
	}
	else
	{
		if ((current_fork_pose->l_fork->fork_n) % 2 != 0)
		{
			if (!ft_eat(philo,
				&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
				&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
				current_fork_pose))
			return (0);
		}
		else
		{
			if (!ft_eat(philo,
					&philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
					&philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
					current_fork_pose))
				return (0);
		}
	}
	if (!ft_sleep(current_fork_pose->l_fork->fork_n, philo))
		return (0);
	return (1);
}
