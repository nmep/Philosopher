/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:34:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/10 22:12:24 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, int *status)
{
	pid_t	pid;


	philo->last_meal = 0;
	pid = fork();
	if (pid == -1)
	{
		*status = ERROR_FORK;
		return (ERROR_FORK);
	}
	if (pid == 0)
	{
		printf("addr de lm %p\n", &philo->last_meal);
		*status = ft_loop_eat(philo, philo_n, &philo->last_meal, pid_tab);
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
		waitpid(pid_tab[i], status, 0);
		*status = WEXITSTATUS(*status);
		if (*status >= 1 && *status <= philo->ph_data.p_number)
		{
			printf("%d %d died\n", ft_print_time(philo, NULL), *status);
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
}

void	*ft_check_death_mt(void *arg_philo)
{
	t_philo *philo;
	// int	i;

	philo = arg_philo;
	// printf("addr de lm %p\n", &philo->last_meal);
	while (1)
	{
		printf("last meal = %d\n", philo->last_meal);
	}
	return (NULL);
}

int	ft_init_routine(t_philo *philo)
{
	int	i;
	int	*pid_tab;
	int	status;
	pthread_t	monitor;

	status = 0;
	philo->dead = 0;
	philo->eat_finish = 0;
	pid_tab = malloc(sizeof(int) * philo->ph_data.p_number);
	if (!pid_tab)
		return (ERROR_MALLOC);
	sem_unlink("/toto");
	philo->fork = sem_open("/toto", O_CREAT, 0644, philo->ph_data.p_number);
	if (!philo->fork)
		return (free(pid_tab), ERROR_SEM);
	i = 0;
	while (i < philo->ph_data.p_number)
	{
		ft_init_philo(philo, i + 1, &pid_tab[i], &status);
		if (status == ERROR_FORK)
			return (free(pid_tab), sem_close(philo->fork), ERROR_FORK);
		i++;
	}
	pthread_create(&monitor, NULL, ft_check_death_mt, philo);
	i = 0;
	// while (i < philo->ph_data.p_number)
	// {
	// 	waitpid(pid_tab[i], &status, 0);
	// 	status = WEXITSTATUS(status);
	// 	if (status >= 1 && status <= philo->ph_data.p_number)
	// 	{
	// 		printf("%d %d died\n", ft_print_time(philo, NULL), status);
	// 		i = 0;
	// 		while (i < philo->ph_data.p_number)
	// 		{
	// 			kill(pid_tab[i], SIGKILL);
	// 			i++;
	// 		}
	// 		break ;
	// 	}
	// 	i++;
	// }
	ft_wait(philo, pid_tab, &status);
	free(pid_tab);
	sem_unlink("/toto");
	sem_close(philo->fork);
	// free(philo->fork);
	return (1);
}
