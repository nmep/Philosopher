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
	pthread_mutex_unlock(&philo->mutex.f_pos_addr_incr);
	i = -1;
	while (++i < philo->ph_data.number_of_time_p_eat)
	{
		ft_philo(philo, current_fork_pose);
	}
	return (NULL);
}
