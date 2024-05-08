/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_conditions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:16:49 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_finish(t_philo *philo)
{
	int	finish;
	int	i;
	int	nb_eat;
	int	nb_philo;

	i = 0;
	finish = 0;
	nb_eat = (*philo).data->nb_must_eat;
	nb_philo = philo[0].data->nb_philo;
	while (i < nb_philo)
	{
		pthread_mutex_lock(philo[i].write);
		if (philo[i].nb_eat >= nb_eat)
			finish++;
		pthread_mutex_unlock(philo[i].write);
		i++;
	}
	if (finish == i && nb_eat)
		return (1);
	return (0);
}

static void	*finish(t_philo *philo, long delay)
{
	if (!delay)
	{
		pthread_mutex_lock(philo->dead_check);
		philo->data->dead = 1;
		pthread_mutex_unlock(philo->dead_check);
		return (NULL);
	}
	pthread_mutex_lock(philo->dead_check);
	philo->data->dead = 1;
	pthread_mutex_unlock(philo->dead_check);
	pthread_mutex_lock(philo->write);
	printf(RED "%5ld %3d died\n" RESET, delay, philo->id);
	pthread_mutex_unlock(philo->write);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*philo;
	int		i;
	long	delay;
	long	last_time;
	int		nb_philo;

	philo = (t_philo *)arg;
	nb_philo = philo[0].data->nb_philo;
	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			if (check_finish(philo))
				return (finish(&(philo[i]), 0));
			delay = get_actual_ms() - (long)philo[i].data->start_time;
			pthread_mutex_lock(philo[i].write);
			last_time = (long)philo[i].last_time_eat;
			pthread_mutex_unlock(philo[i].write);
			if ((long)philo[i].data->time_to_die < delay - last_time)
				return (finish(&(philo[i]), delay));
			i++;
		}
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_check);
	if (philo->data->dead)
		return (pthread_mutex_unlock(philo->dead_check), 1);
	pthread_mutex_unlock(philo->dead_check);
	return (0);
}
