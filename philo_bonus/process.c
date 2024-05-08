/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:16:35 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	long	delay;
	long	last_time;

	philo = (t_philo *)arg;
	while (1)
	{
		delay = get_actual_ms() - (long)philo->data->start_time;
		sem_wait(philo->data->write);
		last_time = (long)philo->last_time_eat;
		sem_post(philo->data->write);
		if ((long)philo->data->time_to_die < delay - last_time)
		{
			sem_wait(philo->data->write);
			printf(RED "%5ld %3d died\n" RESET, delay, philo->id);
			if (philo->data->nb_must_eat)
				while (philo->data->nb_philo-- > 0)
					sem_post(philo->data->remain);
			sem_post(philo->data->dead);
			return (NULL);
		}
	}
	return (NULL);
}

static void	*check_meal(void *arg)
{
	t_data	*data;
	int		count;

	data = (t_data *)arg;
	count = data->nb_philo;
	while (count-- > 0)
		sem_wait(data->remain);
	return (NULL);
}

static int	main_process(t_philo *philo, int i)
{
	philo[i].pid = fork();
	if (philo[i].pid < 0)
		return (free(philo), printf("Error creating process\n"), 1);
	else if (philo[i].pid == 0)
	{
		if (routine(&philo[i]) == NULL)
			return (free(philo), 1);
	}
	return (0);
}

int	start_process(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	count_meal;

	if (data->nb_must_eat)
	{
		if (pthread_create(&count_meal, NULL, check_meal, data) != 0)
			return (printf("pthread_create() failed.\n"), 1);
	}
	i = -1;
	while (++i < philo[0].data->nb_philo)
	{
		if (main_process(philo, i))
			return (pthread_join(count_meal, NULL), 1);
	}
	if (data->nb_must_eat)
	{
		if (pthread_join(count_meal, NULL) != 0)
			return (printf("pthread_join() failed.\n"), 1);
		sem_post(data->dead);
	}
	sem_wait(data->dead);
	while (--i >= 0)
		kill(philo[i].pid, SIGKILL);
	return (0);
}
