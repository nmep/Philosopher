/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/03 16:22:21 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(t_philo *philo, int *tab_data, int len_tab)
{
	int		i;

	i = -1;
	if (len_tab == 4)
		philo->ph_data.number_of_time_p_eat = -1;
	while (++i < len_tab)
		*(((int *) &philo->ph_data) + i) = tab_data[i];
	philo->f_data.fork_pos_state = malloc(sizeof(t_data_fork) * philo->ph_data.p_number);
	if (!philo->f_data.fork_pos_state)
		return (ERROR_MALLOC);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		philo->f_data.fork_pos_state[i].fork_n = i;
	}
	i = -1;
	free(tab_data);
	return (1);
}
