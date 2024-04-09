/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/09 14:27:11 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, int *status)
{
	pid_t	pid;
	int		last_meal;

	last_meal = 0;
	pid = fork();
	if (pid == -1)
		return (ERROR_FORK);
	if (pid == 0)
	{
		*status = ft_loop_eat(philo, philo_n, &last_meal);
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
	int	*pid_tab;
	int	status;

	status = 0;
	pid_tab = malloc(sizeof(int) * philo->ph_data.p_number);
	sem_unlink("/otto");
	philo->fork = sem_open("/otto", O_CREAT, 0644, philo->ph_data.p_number);
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		ft_init_philo(philo, i + 1, &pid_tab[i], &status);
		if (status == ERROR_FORK)
			return (ERROR_FORK);
		i++;
	}
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		waitpid(pid_tab[i], &status, 0);
		status = WEXITSTATUS(status);

		if (status >= 1 && status <= philo->ph_data.p_number)
		{
			printf("%d %d died\n", ft_print_time(philo, NULL), status);
			i = 0;
			while (i < philo->ph_data.p_number)
			{
				kill(pid_tab[i], SIGKILL);
				i++;
			}
			break ;
			
		}
		i++;
	}
	sem_unlink("/otto");
	return (1);
}
