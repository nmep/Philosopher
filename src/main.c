/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:39:08 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/26 11:20:12 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	int		check;

	if (ac != 6)
		return (printf(ERR_MSG), ERR_PARSING);
	check = ft_parsing_data(&philo, av, ac);
	if (check == ERROR_MALLOC)
		return (printf("ERROR MALLOC\n"), ERROR_MALLOC);
	else if (check == ERR_PARSING)
		return (printf(ERR_MSG_PARS), ERR_PARSING);
	check = ft_init_routine(&philo);
	if (check == ERROR_MALLOC)
		return (printf("ERROR MALLOC\n"), ERROR_MALLOC);
	return (0);
}
