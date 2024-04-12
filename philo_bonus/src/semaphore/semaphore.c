/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:25:54 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/12 03:30:15 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_unlink(void)
{
	sem_unlink("/die");
	sem_unlink("/prioritie");
	sem_unlink("/fork");
}

void	ft_sem_close(t_philo *philo)
{
	sem_close(philo->fork);
	sem_close(philo->prioritie);
	sem_close(philo->die);
}

void	ft_clear_sem(t_philo *philo)
{
	ft_sem_unlink();
	ft_sem_close(philo);
}

int	ft_sem_open(t_philo *philo)
{
	philo->prioritie = sem_open("/prioritie", O_CREAT, 0644, 1);
	if (!philo->prioritie)
		return (ERROR_SEM);
	philo->fork = sem_open("/fork", O_CREAT, 0644, philo->ph_data.p_number);
	if (!philo->fork)
		return (sem_close(philo->prioritie), ERROR_SEM);
	return (1);
}
