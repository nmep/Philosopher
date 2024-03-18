/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:12 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 22:14:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIHLO_H
# define PIHLO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

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

typedef struct s_philo_data
{
	int	p_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_p_eat;
}	t_philo_data;

// # ---------------------------------------------	#
// #												#
// #												#
// #				FT_PARSE.C						#
// #												#
// #												#
// # ---------------------------------------------	#

int		ft_parsing_data(t_philo_data *ph_d, char **av, int ac);
int		ft_init_data(t_philo_data *ph_d, int *tab_data);


// # ---------------------------------------------	#
// #												#
// #												#
// #					TOOLS.C						#
// #												#
// #												#
// # ---------------------------------------------	#

int		ft_is_str_atoiable(char *str);
bool	ft_atoi(char *str, int *res);

#endif