/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/05 18:52:22 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_data(t_philo *philo, int *tab_data, int len_tab)
{
	int	i;

	i = -1;
	if (len_tab == 4)
		philo->ph_data.number_of_time_p_eat = -1;
	while (++i < len_tab)
		*(((int *) &philo->ph_data) + i) = tab_data[i];
	free(tab_data);
	return (1);
}
