/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:10:59 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/24 18:31:24 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// fonction servant a assigner x et y fourchette a z pihlosopher
void	ft_fork_number_init(t_fork_pos **fork_pos, int position, int nb_philo)
{
	(*fork_pos)[position].l_fork.fork_number = position;
	(*fork_pos)[position].r_fork.fork_number = position - 1;
	if ((*fork_pos)[position].r_fork.fork_number < 0)
		(*fork_pos)[position].r_fork.fork_number = nb_philo - (position + 1);
	// printf("philo n %d\nfl = %d | fr = %d\n", position, (*fork_pos)[position].l_fork.fork_number, (*fork_pos)[position].r_fork.fork_number);
}

int	ft_init_thread(t_philo *philo)
{
	int	i;
	int	j;
	t_fork_pos	*save_fork_pose;

	i = -1;
	printf("nb de pihlo %d\n", philo->ph_data.p_number);
	philo->fork.fork_pos = malloc (sizeof(t_fork_pos) * philo->ph_data.p_number);// malloc tableau de pose de fork
	while (++i < philo->ph_data.p_number)
		ft_fork_number_init(&philo->fork.fork_pos, i, philo->ph_data.p_number); // init fork pose number
	save_fork_pose = philo->fork.fork_pos; // addresse du pointeur de fork pose
	philo->ph = malloc(sizeof(pthread_t) * philo->ph_data.p_number); // malloc tableau thread philo
	if (!philo->ph)
		return (ERROR_MALLOC);
	philo->fork.tab_fork = malloc(sizeof(pthread_mutex_t) * philo->ph_data.p_number); // malloc talbeau de mutex pour chaque fourchette
	if (!philo->fork.tab_fork)
		return (free(philo->ph), ERROR_MALLOC);
	i = -1;
	while (++i < philo->ph_data.p_number) // init mutex
		pthread_mutex_init(&philo->fork.tab_fork[i], NULL);
	pthread_mutex_init(&philo->fork.fork_pos_incr, NULL);
	i = -1;
	while (++i < philo->ph_data.number_of_time_p_eat) //init threads
	{
		j = -1;
		philo->fork.fork_pos = save_fork_pose;
		while (++j < philo->ph_data.p_number)
		{
			if (pthread_create(&philo->ph[j], NULL, ft_routine, philo) != 0)
				return (free(philo->ph), free(philo->fork.tab_fork), 0);
			// usleep(300);
		}
		j = -1;
		while (++j < philo->ph_data.p_number)
		{
			if (pthread_join(philo->ph[j], NULL) != 0)
				return (free(philo->ph), free(philo->fork.tab_fork), 0);
		}
	}
	pthread_mutex_destroy(&philo->fork.fork_pos_incr);
	while (--i > -1)
		pthread_mutex_destroy(&philo->fork.tab_fork[i]);
	free(philo->ph);
	free(philo->fork.tab_fork);
	return (1);
}
