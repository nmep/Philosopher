/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 05:28:53 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// si len arg = 4 alors le nombre de fois que les philos doivent manger
// est de av[6].
// sinon le nombre de fois sera infini
int	ft_init_data(t_philo_data *ph_d, int *tab_data, int len_tab)
{
	int		*ptr;
	int		i;

	i = -1;
	ptr = (int *) ph_d;
	while (++i <= tab_data[0])
		*(ptr + i) = tab_data[i];
	if (len_tab == 3)
		*(ptr + i) = -1;
	free(tab_data);
	return (1);
}
