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
	t_philo		*philo;
	t_fork_lr	*current_fork_pose;
	int			i;

	current_fork_pose = NULL;
	philo = arg_philo;
	pthread_mutex_lock(&philo->mutex.f_pos_addr_incr);
	current_fork_pose = philo->f_data.ph_fork_pos;
	philo->f_data.ph_fork_pos++;
	// printf("philo %d | ", current_fork_pose->l_fork->fork_n);
	// printf("lf | ph tab %p = %d | fork tab %p = %d\n", current_fork_pose->l_fork, current_fork_pose->l_fork->fork_n, 
	// 	&philo->f_data.fork_pos_state[current_fork_pose->l_fork->fork_n], philo->f_data.fork_pos_state[current_fork_pose->l_fork->fork_n].fork_n);

	// printf("philo %d | ", current_fork_pose->l_fork->fork_n);
	// printf("rf | ph tab %p = %d | fork tab %p = %d\n", current_fork_pose->r_fork, current_fork_pose->r_fork->fork_n, 
	// 	&philo->f_data.fork_pos_state[current_fork_pose->r_fork->fork_n], philo->f_data.fork_pos_state[current_fork_pose->r_fork->fork_n].fork_n);
	pthread_mutex_unlock(&philo->mutex.f_pos_addr_incr);
	i = 0;
	while (i < philo->ph_data.number_of_time_p_eat)
	{
		if (!ft_philo(philo, current_fork_pose))
			break ;
		current_fork_pose->hungry = 0;
		i++;
	}
	return (NULL);
}
