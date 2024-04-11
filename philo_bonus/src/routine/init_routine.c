/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garfi <garfi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/11 16:06:34 by garfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, int *status)
{
	pid_t		pid;
	pthread_t	monitor;

	philo->last_meal = 0;
	philo->id = philo_n;
	pid = fork();
	if (pid == -1)
	{
		*status = ERROR_FORK;
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		pthread_create(&monitor, NULL, (void *) ft_check_death, philo);
		*status = ft_loop_eat(philo, philo_n, &philo->last_meal, pid_tab);
		pthread_join(monitor, NULL);
	}
	else
	{
		*pid_tab = pid;
	}
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
			printf("time %d philo recue comme mort %d\n", ft_print_time(philo, NULL), *status);
			while (++i < philo->ph_data.p_number)
			{
				kill(pid_tab[i], SIGKILL);
			}
			break ;
		}
		i++;
	}
}

int	ft_check_death(void *arg_philo)
{
	t_philo	*philo;
	long	timestamp;

	philo = arg_philo;
	while (1)
	{
		timestamp = ft_print_time(philo, NULL);
		if (philo->last_meal * 2 < philo->ph_data.time_to_eat && philo->ph_data.p_number > 1)
			continue ;
		if (timestamp - philo->last_meal >= philo->ph_data.time_to_die)
		{
			philo->dead = 1;
			printf("%ld %d died\n", timestamp, philo->id);
			exit (philo->id);
		}
	}
	return (0);
}

int	ft_init_routine(t_philo *philo)
{
	int			i;
	int			pid_tab[philo->ph_data.p_number];
	int			status;

	status = 0;
	philo->dead = 0;
	philo->eat_finish = 0;
	sem_unlink("/toto");
	philo->fork = sem_open("/toto", O_CREAT, 0644, philo->ph_data.p_number);
	if (!philo->fork)
		return (ERROR_SEM);
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		ft_init_philo(philo, i + 1, &pid_tab[i], &status);
		if (status == ERROR_FORK)
			return (sem_close(philo->fork), ERROR_FORK);
		i++;
	}
	ft_wait(philo, pid_tab, &status);
	// free(pid_tab);
	sem_unlink("/toto");
	sem_close(philo->fork);
	// free(philo->fork);
	return (1);
}
