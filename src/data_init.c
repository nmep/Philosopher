/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/25 17:16:40 by lgarfi           ###   ########.fr       */
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
	while (++i <= tab_data[0])
		*(((int *) &philo->ph_data) + i) = tab_data[i];
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		philo->fork.fork_pos[i].l_fork.state = 0;
		philo->fork.fork_pos[i].r_fork.state = 0;
	}
	free(tab_data);
	return (1);
}
