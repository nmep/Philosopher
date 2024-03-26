/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 10:55:42 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo(t_philo *philo)
{
	t_fork_pos *current_fork_pose;

	current_fork_pose = NULL;
	ft_init_fork_data(philo, current_fork_pose);
	printf("philo n %d lf %d rf %d\n", current_fork_pose->l_fork.fork_number, current_fork_pose->l_fork.fork_number, current_fork_pose->r_fork.fork_number);
	// if (!ft_check_fork(current_fork_pose))
	// {
	// 	ft_sleep(current_fork_pose->l_fork.fork_number, philo);
	// 	ft_think(current_fork_pose->l_fork.fork_number, philo);
	// }
	// if (current_fork_pose->l_fork.fork_number < current_fork_pose->r_fork.fork_number)
	// 	ft_get_fork(philo->fork.tab_fork[current_fork_pose->l_fork.fork_number], philo->fork.tab_fork[current_fork_pose->r_fork.fork_number]);
	// else
	// 	ft_get_fork();
	// ft_eat();
	return (1);
}