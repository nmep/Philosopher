/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:00:33 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/25 16:00:00 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	char *ptr;

	if (!str)
		return (0);
	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

int	ft_is_str_atoiable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
			&& (str[i] != '-' && str[i] != '+'))
			return (0);
		i++;
	}
	return (1);
}

bool	ft_atoi(char *str, int	*res)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	while (str[i] && (str[i] == ' '
			|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if ((*res > INT_MAX / 10 || (*res == INT_MAX / 10
					&& (str[i] + 48) > INT_MAX % 10)) || s == -1)
			return (false);
		*res = (*res) * 10 + (str[i] - 48);
		i++;
	}
	*res *= s;
	return (true);
}

inline void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	write (1, &"0123456789"[nb % 10], 1);
}
