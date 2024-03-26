// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
// /*                                               J +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/19 20:50:54 by lgarfi            #+#    #+#             */
// /*   Updated: 2024/03/21 18:27:27 by lgarfi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg_philo)
{
	t_philo	*philo;
	t_fork_pos *current_fork_pose;
	philo = arg_philo; // prendre le parametre du

	ft_init_fork_data(philo, current_fork_pose);
	if (!ft_check_fork(current_fork_pose))
	{
		ft_sleep(current_fork_pose->l_fork.fork_number, philo);
		ft_think(current_fork_pose->l_fork.fork_number, philo);
	}
	if (current_fork_pose->l_fork.fork_number < current_fork_pose->r_fork.fork_number)
		ft_get_fork(philo->fork.tab_fork[current_fork_pose->l_fork.fork_number], philo->fork.tab_fork[current_fork_pose->r_fork.fork_number]);
	else
		ft_get_fork();
	ft_eat();
	return (NULL);
}
