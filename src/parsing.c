/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:40 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 22:40:58 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// va check dans av si les arg sont bons a etre pris en compte
// attention si il est possible que philo se lance avec moin de 5 arg il faudra 
// check le cas d'erreur
int	ft_parsing_data(t_philo_data *ph_d, char **av, int ac)
{
	int	i;
	int	j;
	int	*tab_data;

	i = 1;
	(void)ph_d;
	while (i < ac)
	{
		if (!ft_is_str_atoiable(av[i]))
			return (0);
		i++;
	}
	tab_data = malloc(sizeof(int) * 5);
	if (!tab_data)
		return (printf("ERROR MALLOC\n"), ERROR_MALLOC);
	i = 1;
	j = 0;
	while (i < ac)
	{
		if (!ft_atoi(av[i++], &tab_data[j++]))
			return (free(tab_data), 0);
	}
	ft_init_data(ph_d, tab_data);
	return (1);
}
