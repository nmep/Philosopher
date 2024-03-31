/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:56:45 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/18 12:16:14 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

// struct	timeval
// {
// 	time_t		tv_sec;     /* seconds */
// 	suseconds_t	tv_usec;    /* microseconds */
// };

int	main(int ac, char **av)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("temps en micro seconde = %ld\n", tv.tv_usec);
	printf("temps en milli seconde = %ld\n", tv.tv_usec);
	// printf("temps en seconde = %ld\n"
	// 		"tmeps en microsecode = %ld\n"
	// 		"temps en milliseconde %ld\n",
	// 			tv.tv_sec, tv.tv_usec, tv.tv_usec * 0.0001);
}