/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/06 01:06:53 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, sem_t *forks)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERROR_FORK);
	if (pid == 0)
	{
		ft_loop_eat(philo, philo_n, forks);
	}
	else
	{
		*pid_tab = pid;
	}
	return (1);
}

int	ft_init_routine(t_philo *philo)
{
	int	i;
	int	check;
	int	*pid_tab;

	pid_tab = malloc(sizeof(int) * philo->ph_data.p_number);
	sem_open(&philo->fork, O_CREAT, )
	i = 0;
	check = 0;
	while (i < philo->ph_data.p_number)
	{
		check = ft_init_philo(philo, i + 1, &pid_tab[i], &philo->fork);
		if (check == ERROR_FORK)
			return (ERROR_FORK);
		i++;
	}
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		waitpid(0, NULL, 0);
		i++;
	}
	return (1);
}
