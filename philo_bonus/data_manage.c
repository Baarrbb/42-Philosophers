/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:09:15 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:04:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_sem(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/remain");
	data->forks = sem_open("/fork", O_CREAT | O_EXCL, 0600, data->nb_philo);
	data->write = sem_open("/write", O_CREAT | O_EXCL, 0600, 1);
	data->dead = sem_open("/dead", O_CREAT | O_EXCL, 0600, 0);
	data->remain = sem_open("/remain", O_CREAT | O_EXCL, 0600, 0);
	if (data->forks == SEM_FAILED || data->write == SEM_FAILED
		|| data->dead == SEM_FAILED || data->remain == SEM_FAILED)
		return (printf("Error creating semaphore\n"), -1);
	return (0);
}

int	fill_data(t_data *data, char **av, int six_arg)
{
	memset(data, 0, sizeof(t_data));
	data->start_time = get_actual_ms();
	if (data->start_time < 0)
		return (printf("Parsing start_time failed\n"), -1);
	data->nb_philo = parse_param(av[1]);
	if (data->nb_philo < 0)
		return (printf("Parsing nb_philo failed.\n"), -1);
	data->time_to_die = parse_param(av[2]);
	if (data->time_to_die < 0)
		return (printf("Parsing time_to_die failed.\n"), -1);
	data->time_to_eat = parse_param(av[3]);
	if (data->time_to_eat < 0)
		return (printf("Parsing time_to_eat failed.\n"), -1);
	data->time_to_sleep = parse_param(av[4]);
	if (data->time_to_sleep < 0)
		return (printf("Parsing time_to_sleep failed.\n"), -1);
	if (six_arg == 6)
	{
		data->nb_must_eat = parse_param(av[5]);
		if (data->nb_must_eat < 0)
			return (printf("Parsing "
					"number_of_times_each_philosopher_must_eat failed.\n"), -1);
	}
	init_sem(data);
	return (0);
}

t_philo	*init_philo(t_data *data)
{
	t_philo		*ph;
	int			i;

	ph = (t_philo *)malloc((data->nb_philo + 1) * sizeof(t_philo));
	if (!ph)
		return (printf("malloc() philosophers failed\n"), NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		memset(&ph[i], 0, sizeof(t_philo));
		ph[i].id = i + 1;
		ph[i].data = data;
	}
	memset(&ph[i], 0, sizeof(t_philo));
	return (ph);
}
