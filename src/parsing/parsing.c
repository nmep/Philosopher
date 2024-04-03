/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:40 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/03 19:54:10 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// va check dans av si les arg sont bons a etre pris en compte
// attention si il est possible que philo se lance avec moin de 5 arg il faudra 
// check le cas d'erreur// va check dans av si les arg sont bons a etre pris en compte
// attention si il est possible que philo se lance avec moin de 5 arg il faudra 
// check le cas d'erreur
int	ft_parsing_data(t_philo *philo, char **av, int ac)
{
	int	i;
	int	j;
	int	*tab_data;

	i = 0;
	while (++i < ac)
	{
		if (!ft_is_str_atoiable(av[i]))
			return (ERR_PARSING);
	}
	tab_data = malloc(sizeof(int) * (5));
	if (!tab_data)
		return (printf("ERROR MALLOC\n"), ERROR_MALLOC);
	i = 0;
	j = 0;
	while (++i < ac)
	{
		tab_data[j] = 0;
		if (!ft_atoi(av[i], &tab_data[j]))
			return (free(tab_data), ERR_PARSING);
		j++;
	}
	if (ft_init_data(philo, tab_data, ac - 1) == ERROR_MALLOC)
		return (free(tab_data), ERROR_MALLOC);
	return (1);
}
