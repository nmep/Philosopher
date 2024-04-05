/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:12 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/06 01:06:04 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_PARSING 2
# define ERROR_MALLOC 3
# define ERROR_FORK 4

typedef struct s_philo_data
{
	int	p_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_p_eat;
}	t_philo_data;

typedef struct s_time
{
	long start;
}	t_time;

typedef struct s_pihlo
{
	pthread_t		*ph;
	t_philo_data	ph_data;
	sem_t			fork;
	t_time			time;
}	t_philo;

// # ---------------------------------------------	#
// #												#
// #												#
// #				PARSING							#
// #												#
// #												#
// # ---------------------------------------------	#

// data init.c
int		ft_init_data(t_philo *philo, int *tab_data, int len_tab);

// parsing.c
int		ft_parsing_data(t_philo *philo, char **av, int ac);

// # ---------------------------------------------	#
// #												#
// #												#
// #				INIT ROUTINE					#
// #												#
// #												#
// # ---------------------------------------------	#

// ft_init_philo
int		ft_init_philo(t_philo *philo, int philo_n, int *pid_tab, sem_t *forks);

// ft_init_routine.c
int		ft_init_routine(t_philo *philo);

// # ---------------------------------------------	#
// #												#
// #												#
// #					ROUTINE						#
// #												#
// # ---------------------------------------------	#

// ft_loop_eat.c
int		ft_loop_eat(t_philo *philo, int philo_n, sem_t *forks);

// ft_routine.c
int		ft_routine(t_philo *philo, int philo_n, sem_t *forks);

// ft_philo_actions.c
int		ft_think(t_philo *philo, int philo_n);
int		ft_sleep(t_philo *philo, int philo_n);
int		ft_eat(t_philo *philo, int philo_n, sem_t *forks);

// ft_time_gestion.c
long	ft_get_time_milli();
int		ft_print_time(t_philo *philo);
int		ft_usleep(t_philo *philo, int time_to_wait);


// # ---------------------------------------------	#
// #												#
// #												#
// #					TOOLS						#
// #												#
// #												#
// # ---------------------------------------------	#

// tools.c
int		ft_strlen(char *str);
int		ft_is_str_atoiable(char *str);
bool	ft_atoi(char *str, int *res);

#endif