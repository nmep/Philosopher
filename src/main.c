/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:39:08 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 17:11:42 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo_data	ph_d;

	if (ac < 6)
		return (printf(ERR_MSG), ERR_PARSING);
	if (!ft_parsing_data(&ph_d, av, ac))
		return (printf(ERR_MSG_PARS), ERR_PARSING);
	
}