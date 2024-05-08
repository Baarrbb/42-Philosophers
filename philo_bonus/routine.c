/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:11:32 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_state(char *state, t_philo **philo, int eat)
{
	long int	actual_ms;

	actual_ms = 0;
	sem_wait((*philo)->data->write);
	actual_ms = get_actual_ms() - (*philo)->data->start_time;
	printf("%5ld %3d %s\n", actual_ms, (*philo)->id, state);
	if (eat)
	{
		(*philo)->last_time_eat = actual_ms;
		(*philo)->nb_eat++;
		if ((*philo)->nb_eat == (*philo)->data->nb_must_eat)
			sem_post((*philo)->data->remain);
	}
	sem_post((*philo)->data->write);
	return ;
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

static void	one_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_state("has taken a fork", &philo, 0);
}

void	*routine(t_philo *philo)
{
	pthread_t	death;

	if (pthread_create(&death, NULL, check_death, philo) != 0)
		return (printf("pthread_create() failed.\n"), NULL);
	if (philo->data->nb_philo == 1)
		one_fork(philo);
	start_routine(philo);
	while (1)
	{
		sem_wait(philo->data->forks);
		sem_wait(philo->data->forks);
		print_state("has taken a fork", &philo, 0);
		print_state("has taken a fork", &philo, 0);
		print_state("is eating", &philo, 1);
		usleep(philo->data->time_to_eat * 1000);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_state("is sleeping", &philo, 0);
		usleep(philo->data->time_to_sleep * 1000);
		print_state("is thinking", &philo, 0);
		philo_think(philo);
	}
	if (pthread_join(death, NULL) != 0)
		return (printf("pthread_join() failed.\n"), NULL);
	return (NULL);
}
