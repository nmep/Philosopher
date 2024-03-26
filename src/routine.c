// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
// /*                                               J +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/19 20:50:54 by lgarfi            #+#    #+#             */
// /*   Updated: 2024/03/21 18:27:27 by lgarfi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg_philo)
{
	t_philo		*philo;
	int			i;

	philo = arg_philo;
	i = 0;
	while (i < philo->ph_data.number_of_time_p_eat)
	{
		if (!ft_philo(philo))
			break ;
		i++;
	}
	return (NULL);
}
