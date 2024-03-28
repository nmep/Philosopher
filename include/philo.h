/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:12 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/28 14:05:12 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIHLO_H
# define PIHLO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ERR_MSG "argument should be enter as follow\n"\
				"ARG 1 [number_of_philosophers]\n"     \
				"ARG 2 [time_to_die]\n"                \
				"ARG 3 [time_to_eat]\n"                \
				"ARG 4 [time_to_sleep]\n"              \
				"ARG 5 [number_of_times_each_philosopher_must_eat]\n"

# define ERR_MSG_PARS "arguments should enter as follow\n" \
						"ARG 1 [int > 0]\n"                  \
						"ARG 2 [int > 0]\n"                  \
						"ARG 3 [int > 0]\n"                  \
						"ARG 4 [int > 0]\n"                  \
						"ARG 5 [int > 0]\n"

# define ERR_PARSING 2
# define ERROR_MALLOC 3

// numero de la fourchette et son etat (prise ou pas)
typedef struct s_state_fork
{
	int	fork_n;
	int	state;
}	t_data_fork;

// repsente une cause du tableau ph fork pos avec 
// l fork l'adresse de la case du tableau repsentant la fourchette
// gauche ou droite pour x philo avec son etat (modifiable au besoin)
typedef struct s_fork_lr
{
	t_data_fork *l_fork;
	t_data_fork *r_fork;
	int			hungry;
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
	pthread_mutex_t	f_state;
	pthread_mutex_t	*tab_fork;
	pthread_mutex_t	f_pos_addr_incr;
	pthread_mutex_t time;
	pthread_mutex_t	print;
	
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
	int				micro_time;
}	t_time;

typedef struct s_pihlo
{
	pthread_t		*ph;
	t_philo_data	ph_data;
	t_fork_data		f_data;
	t_mutex			mutex;
	t_time			time;
	
}	t_philo;

// # ---------------------------------------------	#
// #												#
// #												#
// #				FT_PARSE.C						#
// #												#
// #												#
// # ---------------------------------------------	#

int		ft_parsing_data(t_philo *philo, char **av, int ac);
int		ft_init_data(t_philo *philo, int *tab_data);

// # ---------------------------------------------	#
// #												#
// #												#
// #			ft_init_routineS.C					#
// #												#
// #												#
// # ---------------------------------------------	#

int		ft_init_routine(t_philo *philo);
int		ft_init_routine_data(t_philo *philo, t_fork_lr *save_fork_pose);

// # ---------------------------------------------	#
// #												#
// #												#
// #				FT_ROUTINE.C					#
// #												#
// #												#
// # ---------------------------------------------	#

void		*ft_routine(void *arg_philo);

// # ---------------------------------------------	#
// #												#
// #												#
// #				FT_PHILO.C						#
// #												#
// #												#
// # ---------------------------------------------	#

int			ft_philo(t_philo *philo, t_fork_lr *current_fork_pose);
void		ft_think(t_philo *philo, int philo_n);
void		ft_eat(t_philo *philo, pthread_mutex_t first_lock, pthread_mutex_t second_lock, t_fork_lr *current_pose);
int			ft_check_fork(t_fork_lr *fork_pose, t_philo *philo);
void		ft_sleep(int philo_n, t_philo *philo);

// # ---------------------------------------------	#
// #												#
// #												#
// #					TOOLS.C						#
// #												#
// #												#
// # ---------------------------------------------	#

int		ft_is_str_atoiable(char *str);
bool	ft_atoi(char *str, int *res);
void	ft_putnbr(int nb);

#endif