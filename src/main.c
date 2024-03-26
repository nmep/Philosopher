/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:39:08 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/25 15:23:19 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 6)
		return (printf(ERR_MSG), ERR_PARSING);
	if (ft_parsing_data(&philo, av, ac) != 1)
		return (printf(ERR_MSG_PARS), ERR_PARSING);
	if (ft_init_thread(&philo) != 1)
		return (2);
	return (0);
}
