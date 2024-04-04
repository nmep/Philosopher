/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:18:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/04 08:25:29 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// fonction pour trouver un philo a qu'elle fourchette de gauche et de droite
void	ft_get_fork(t_philo *philo, int i)
{
	philo->f_data.ph_fork_pos[i].l_fork = &philo->f_data.fork_pos_state[i];
	if ((i - 1) < 0)
	{
		philo->f_data.ph_fork_pos[i].r_fork = \
			&philo->f_data.fork_pos_state[(philo->ph_data.p_number - (i + 1))];
	}
	else
		philo->f_data.ph_fork_pos[i].r_fork = \
			&philo->f_data.fork_pos_state[i - 1];
	philo->f_data.ph_fork_pos[i].last_meal = 0;
}

// fonction servant a assigner x et y fourchette a z pihlosopher
int	ft_fork_position_init(t_philo *philo, t_fork_lr **save_fork_pose)
{
	int	i;

	philo->f_data.ph_fork_pos = \
		malloc(sizeof(t_fork_lr) * philo->ph_data.p_number);
	if (!philo->f_data.ph_fork_pos)
		return (ERROR_MALLOC);
	*save_fork_pose = philo->f_data.ph_fork_pos;
	i = -1;
	while (++i < philo->ph_data.p_number)
		ft_get_fork(philo, i);
	return (1);
}
