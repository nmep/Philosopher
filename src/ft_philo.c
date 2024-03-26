/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 22:24:49 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// faire incrementer ph_data_fork ou jsp quoi pour qvoir les pointeurs des fourchettes
int	ft_philo(t_philo *philo)
{
	t_fork_lr *current_fork_pose;

	current_fork_pose = NULL;
	pthread_mutex_lock(&philo->mutex.f_pos_incr);
	current_fork_pose = philo->f_data.ph_fork_pos;
	philo->f_data.ph_fork_pos++;
	pthread_mutex_unlock(&philo->mutex.f_pos_incr);
	
	// pthread_mutex_lock(&philo->mutex.f_pos_addr_incr);
	printf("philo %d\n", current_fork_pose->l_fork->fork_n);
	// pthread_mutex_unlock(&philo->mutex.f_pos_addr_incr);

	// if (!ft_check_fork(current_fork_pose))
	// 	ft_think(current_fork_pose->l_fork.fork_number, philo);
	// if (current_fork_pose->l_fork.fork_number < current_fork_pose->r_fork.fork_number)
	// 	ft_eat(philo, philo->fork.tab_fork[current_fork_pose->l_fork.fork_number],
	// 		philo->fork.tab_fork[current_fork_pose->r_fork.fork_number], current_fork_pose);
	// else
	// 	ft_eat(philo, philo->fork.tab_fork[current_fork_pose->r_fork.fork_number],
	// 		philo->fork.tab_fork[current_fork_pose->l_fork.fork_number], current_fork_pose);
	// ft_sleep(current_fork_pose->r_fork.fork_number, philo);
	return (1);
}