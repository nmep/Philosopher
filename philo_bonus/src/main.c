/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:39:08 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/05 19:44:45 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_err_msg(void)
{
	printf("argument should be enter as follow\n"\
				"ARG 1 [number_of_philosophers]\n"\
				"ARG 2 [time_to_die]\n"\
				"ARG 3 [time_to_eat]\n"\
				"ARG 4 [time_to_sleep]\n"\
				"ARG 5 [number_of_times_each_philosopher_must_eat]\n");
}

void	ft_print_err_parsing(void)
{
	printf("arguments should enter as follow\n" \
						"ARG 1 [int >= 0]\n"\
						"ARG 2 [int >= 0]\n"\
						"ARG 3 [int >= 0]\n"\
						"ARG 4 [int >= 0]\n"\
						"ARG 5 [int >= 0]\n");
}

int	main(int ac, char **av)
{
	int	check;
	struct timeval	tv;
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (ft_print_err_msg(), ERR_PARSING);
	check = ft_parsing_data(&philo, av, ac);
	if (check == ERROR_MALLOC)
		return (write(2, "ERROR MALLOC\n", 13), ERROR_MALLOC);
	else if (check == ERR_PARSING)
		return (ft_print_err_parsing(), ERR_PARSING);
	gettimeofday(&tv, NULL);
	philo.time.start = (tv.tv_sec * 1000) + tv.tv_usec * 0.001;
	check = ft_init_routine(&philo);
	if (check == ERROR_MALLOC)
		return (write(2, "ERROR MALLOC\n", 13), ERROR_MALLOC);
	return (0);
}
