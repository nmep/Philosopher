/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 20:39:57 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// si len arg = 4 alors le nombre de fois que les philos doivent manger
// est de av[6].
// sinon le nombre de fois sera infini
int	ft_init_data(t_philo *philo, int *tab_data)
{
	int		i;

	i = -1;
	// le dernier argument est optionnel, 
	//si len de tab_data est de 4 c'est qu'il n'y a pas le dernier arg
	while (++i <= 4)
		*(((int *) &philo->ph_data) + i) = tab_data[i];
	philo->f_data.fork_pos_state = malloc(sizeof(t_data_fork) * philo->ph_data.p_number);
	if (!philo->f_data.fork_pos_state)
		return (ERROR_MALLOC);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		philo->f_data.fork_pos_state[i].fork_n = i;
		philo->f_data.fork_pos_state[i].state = 0;
	}
	i = -1;
	free(tab_data);
	return (1);
}
