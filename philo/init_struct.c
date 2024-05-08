/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:23:50 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data->dead_mut), NULL) != 0)
		return (printf("pthread_mutex_init() failed on dead_mut\n"), -1);
	if (pthread_mutex_init(&(data->write_mut), NULL) != 0)
	{
		pthread_mutex_destroy(&data->dead_mut);
		return (printf("pthread_mutex_init() failed on write_mut\n"), -1);
	}
	return (0);
}

int	fill_data(t_data *data, char **av, int six_arg)
{
	memset(data, 0, sizeof(t_data));
	if (init_mutex(data) < 0)
		return (-1);
	data->start_time = get_actual_ms();
	if (data->start_time < 0)
		return (printf("Parsing start_time failed\n"), -1);
	data->nb_philo = parse_param(av[1]);
	if (data->nb_philo < 0)
		return (printf("Parsing nb_philo failed.\n"), -1);
	if (data->nb_philo == 0)
		return (printf(RED "[Error]\n" RESET "Need more philo.\n"), -1);
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
		data->nb_must_eat = parse_param(av[5]);
	if (data->nb_must_eat < 0)
		return (printf("nb_of_times_each_philo_must_eat failed.\n"), -1);
	return (0);
}

static int	sanitize_mut(char *s, t_data *data, t_philo *philo, int id)
{
	int	i;

	printf("%s\n", s);
	pthread_mutex_destroy(&data->dead_mut);
	pthread_mutex_destroy(&data->write_mut);
	if (id)
	{
		i = -1;
		while (++i < id)
			pthread_mutex_destroy(&(philo[i].l_fork));
	}
	free(philo);
	philo = 0;
	return (1);
}

int	init_philo(t_philo **ph, t_data *data)
{
	int	i;

	*ph = (t_philo *)malloc((data->nb_philo) * sizeof(t_philo));
	if (!(*ph))
		return (sanitize_mut("malloc() philo failed", data, *ph, 0));
	i = -1;
	i = -1;
	while (++i < data->nb_philo)
	{
		memset(&(*ph)[i], 0, sizeof(t_philo));
		(*ph)[i].id = i + 1;
		(*ph)[i].data = data;
		if (pthread_mutex_init(&((*ph)[i].l_fork), NULL) != 0)
			return (sanitize_mut("mutex_init() failed on fork", data, *ph, i));
		if (i != 0)
			(*ph)[i].r_fork = &((*ph)[i - 1].l_fork);
		(*ph)[i].dead_check = &(data->dead_mut);
		(*ph)[i].write = &(data->write_mut);
	}
	(*ph)[0].r_fork = &((*ph)[data->nb_philo - 1].l_fork);
	return (0);
}
