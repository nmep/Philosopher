/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:59:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 22:47:14 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(t_philo_data *ph_d, int *tab_data)
{
	int		*ptr;
	int		i;

	i = 0;
	ptr = (int *) ph_d;
	while (i < tab_data[0])
	{
		*(ptr + i) = tab_data[i];
		i++;
	}
	free(tab_data);
	return (1);
}