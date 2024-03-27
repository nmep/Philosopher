/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:45:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/27 23:33:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// faire incrementer ph_data_fork ou jsp quoi pour qvoir les pointeurs des fourchettes
inline int	ft_philo(t_philo *philo, t_fork_lr *current_fork_pose)
{
	if (ft_check_fork(current_fork_pose, philo)) // check sur le tableau de fork
	{
		// printf("philo %d a ses fourchette de dispo\n", current_fork_pose->l_fork->fork_n);
		if (current_fork_pose->l_fork->fork_n < current_fork_pose->r_fork->fork_n)
			ft_eat(philo, philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
				philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], current_fork_pose);
		else if (current_fork_pose->r_fork->fork_n < current_fork_pose->l_fork->fork_n)
			ft_eat(philo, philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
					philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose);
		ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	}
	if (!ft_check_fork(current_fork_pose, philo))
		ft_think(philo, current_fork_pose->l_fork->fork_n);
	if (current_fork_pose->hungry == 0)
	{
		if (current_fork_pose->l_fork->fork_n < current_fork_pose->r_fork->fork_n)
			ft_eat(philo, philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n],
				philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n], current_fork_pose);
		else if (current_fork_pose->r_fork->fork_n < current_fork_pose->l_fork->fork_n)
			ft_eat(philo, philo->mutex.tab_fork[current_fork_pose->r_fork->fork_n],
					philo->mutex.tab_fork[current_fork_pose->l_fork->fork_n], current_fork_pose);
		ft_sleep(current_fork_pose->l_fork->fork_n, philo);
	}
	if (current_fork_pose->hungry == 0)
		ft_think(philo, current_fork_pose->l_fork->fork_n);
	// printf("philo %d a manger %d fois\n", current_fork_pose->l_fork->fork_n,
	// 	current_fork_pose->hungry);
	// if (current_fork_pose->hungry < philo->ph_data.number_of_time_p_eat)
	// 	ft_philo(philo, current_fork_pose);
	// printf("philo %d n'a pas ses fourchette de dispo\n", current_fork_pose->l_fork->fork_n);
	return (1);
}
