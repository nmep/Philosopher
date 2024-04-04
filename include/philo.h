/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:12 by lgarfi            #+#    #+#             */
/*   Updated: 2024/04/04 10:09:56 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ERR_PARSING 2
# define ERROR_MALLOC 3

// numero de la fourchette et son etat (prise ou pas)
typedef struct s_state_fork
{
	int	fork_n;
}	t_data_fork;

// repsente une cause du tableau ph fork pos avec 
// l fork l'adresse de la case du tableau repsentant la fourchette
// gauche ou droite pour x philo avec son etat (modifiable au besoin)
typedef struct s_fork_lr
{
	t_data_fork	*l_fork;
	t_data_fork	*r_fork;
	int			last_meal;
}	t_fork_lr;

// - fork_pos_state est le tableau de toute les fourchettes dispo et leurs etats
// - ph fork pos est la second qui rempresente les emplacement gauche et droite
// de chaque fourchette avec leurs etat modifialbe
typedef struct s_fork
{
	t_data_fork		*fork_pos_state;
	t_fork_lr		*ph_fork_pos;
}	t_fork_data;

typedef struct s_mutex
{
	pthread_mutex_t	*tab_fork;
	pthread_mutex_t	f_pos_addr_incr;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_mutex;

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
	struct timeval	timestamp;
	long			time_start;
}	t_time;

typedef struct s_pihlo
{
	pthread_t		*ph;
	t_philo_data	ph_data;
	t_fork_data		f_data;
	t_mutex			mutex;
	t_time			time;
	int				dead;
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

// ft_fork_init.c
void	ft_get_fork(t_philo *philo, int i);
int		ft_fork_position_init(t_philo *philo, t_fork_lr **save_fork_pose);

// ft_init_routine.c
int		ft_init_routine_data(t_philo *philo, t_fork_lr **save_fork_pose);
void	ft_init_mutex(t_philo *philo);
void	ft_clean_routine_data(t_philo *philo,
			t_fork_lr *save_fork_pose, int *i);
int		ft_init_routine(t_philo *philo);

// # ---------------------------------------------	#
// #												#
// #												#
// #					ROUTINE						#
// #												#
// # ---------------------------------------------	#

// ft_loop_eat.c
void	ft_loop_n_time(t_philo *philo, t_fork_lr *current_fork_pose);
void	ft_infinite_loop(t_philo *philo, t_fork_lr *current_fork_pose);
void	*ft_loop_eat_n_time(void *arg_philo);

// ft_routine.c
int		ft_routine(t_philo *philo, t_fork_lr *current_fork_pose);

// ft_philo_actions.c
int		ft_think(t_philo *philo, int philo_n);
int		ft_sleep(int philo_n, t_philo *philo);
int		ft_eat(t_philo *philo, pthread_mutex_t *first_lock,
			pthread_mutex_t *second_lock, t_fork_lr *current_pose);
int		ft_is_dead(t_philo *philo, t_fork_lr *current_fork_pose);

// ft_time_gestion.c
long	ft_print_time(t_philo *philo, int *last_meal);
long	ft_timestamp(void);
void	ft_usleep(int elapsed, t_philo *philo);

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