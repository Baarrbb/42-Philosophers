/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:46:23 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print_state("has taken a fork", &philo, 0);
	pthread_mutex_unlock(&philo->l_fork);
	return (NULL);
}

static void	eating(t_philo *ph)
{
	if (ph->id != 1)
	{
		ph->first = &ph->l_fork;
		ph->second = ph->r_fork;
	}
	else
	{
		ph->first = ph->r_fork;
		ph->second = &ph->l_fork;
	}
	pthread_mutex_lock(ph->first);
	print_state("has taken a fork", &ph, 0);
	pthread_mutex_lock(ph->second);
	print_state("has taken a fork", &ph, 0);
}

static void	start_routine(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
		if (philo->id % 2 == 1)
			usleep(philo->data->time_to_eat * 1000);
	if (philo->data->nb_philo % 2 == 1)
	{
		if (philo->id % 2 == 1)
			usleep(philo->data->time_to_eat * 1000);
		if (philo->id == 1)
			usleep(philo->data->time_to_eat * 1000);
	}
}

static void	philo_think(t_philo *philo)
{
	int	t_eat;
	int	t_sleep;

	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	if (philo->data->nb_philo % 2 == 0)
	{
		if (t_eat - t_sleep >= 0)
			usleep((t_eat - t_sleep) * 1000);
	}
	else
	{
		if ((t_eat * 2) - t_sleep >= 0)
			usleep(((t_eat * 2) - t_sleep) * 1000);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (one_fork(philo));
	start_routine(philo);
	while (1)
	{
		if (check_if_dead(philo))
			return (NULL);
		eating(philo);
		print_state("is eating", &philo, 1);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->second);
		pthread_mutex_unlock(philo->first);
		print_state("is sleeping", &philo, 0);
		usleep(philo->data->time_to_sleep * 1000);
		print_state("is thinking", &philo, 0);
		if (check_if_dead(philo))
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}
