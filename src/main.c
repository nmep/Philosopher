/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:39:08 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 23:39:39 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo_data	ph_d;
	pthread_t		*phil;
	pthread_mutex_t	*fork;

	if (ac != 6)
		return (printf(ERR_MSG), ERR_PARSING);
	if (ft_parsing_data(&ph_d, av, ac) != 1)
		return (printf(ERR_MSG_PARS), ERR_PARSING);
	phil[ph_d.p_number];
	fork[ph_d.p_number];
	if (ft_init_thread(&phil, ph_d, fork) != 1)
		return (2)
}
