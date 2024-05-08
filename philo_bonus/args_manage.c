/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:04:59 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

static int	ft_atoi(const char *nptr)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	if (i != ft_strlen((char *)nptr))
		return (-1);
	return (res);
}

int	parse_param(char *arg)
{
	int	nb;

	nb = ft_atoi(arg);
	if (nb < 0)
	{
		printf(RED BOLD "[Error] " RESET);
		printf(RED "Problem parsing parameters.\n" RESET);
		return (-1);
	}
	return (nb);
}

long int	get_actual_ms(void)
{
	struct timeval	tv;
	time_t			sec;
	suseconds_t		micro;
	long int		ms;

	if (gettimeofday(&tv, NULL) < 0)
		return (printf("gettimeofday() failed.\n"), -1);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	ms = ((long int)sec * 1000) + ((long int)micro / 1000);
	return (ms);
}
