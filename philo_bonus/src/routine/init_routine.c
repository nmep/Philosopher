/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 03:38:06 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, int *status)
{
	pid_t		pid;
	pthread_t	monitor;

	philo->last_meal = 0;
	philo->dead = 0;
	philo->id = philo_n;
	monitor = 0;
	pid = fork();
	if (pid == -1)
	{
		*status = ERROR_FORK;
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		free(pid_tab);
		pthread_create(&monitor, NULL, (void *) ft_check_death, philo);
		*status = ft_loop_eat(philo, philo_n, &philo->last_meal);
		pthread_join(monitor, NULL);
	}
	else
		pid_tab[philo_n - 1] = pid;
	return (1);
}

void	ft_wait(t_philo *philo, int *pid_tab, int *status)
{
	int	i;

	i = 0;
	while (i < philo->ph_data.p_number)
	{
		waitpid(0, status, 0);
		*status = WEXITSTATUS(*status);
		if (*status >= 1 && *status <= philo->ph_data.p_number)
		{
			i = -1;
			while (++i < philo->ph_data.p_number)
				kill(pid_tab[i], SIGKILL);
			break ;
		}
		i++;
	}
}

int	ft_init_routine(t_philo *philo)
{
	int			i;
	int			*pid_tab;
	int			status;

	status = 0;
	philo->eat_finish = 0;
	ft_sem_unlink();
	philo->prioritie = sem_open("/prioritie", O_CREAT, 0644, 1);
	philo->fork = sem_open("/fork", O_CREAT, 0644, philo->ph_data.p_number);
	pid_tab = malloc(sizeof(int) * philo->ph_data.p_number);
	if (!pid_tab)
		return (ft_clear_sem(philo), printf("ERROR malloc\n"), ERROR_MALLOC);
	i = -1;
	while (++i < philo->ph_data.p_number)
	{
		ft_init_philo(philo, i + 1, pid_tab, &status);
		if (status == ERROR_FORK)
			return (free(pid_tab), ft_sem_unlink(),
				ft_sem_close(philo), ERROR_FORK);
	}
	ft_wait(philo, pid_tab, &status);
	free(pid_tab);
	ft_clear_sem(philo);
	return (1);
}
