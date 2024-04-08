/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/08 17:30:08 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERROR_FORK);
	if (pid == 0)
	{
		printf("dans enfant philo %d\n", philo_n);
		*status = ft_loop_eat(philo, philo_n, philo->fork);
		printf("apres exit\n");
	}
	else
	{
		printf("parent\n");
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
	philo->fork = sem_open("/fork", O_CREAT, 0644, philo->ph_data.p_number);
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		if ((i + 1) % 2 != 0)
			ft_usleep(philo->ph_data.time_to_eat);
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
		// print ici que x philo est mort
		// pour bien le gerer faire en sorte que l'enfant return 
		// l'id du philo qui est mort
		i++;
	}
	sem_unlink("/fork");
	return (1);
}
