/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:40:16 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_manage(void)
{
	printf(RED BOLD "[Error] " RESET);
	printf(RED "Invalid number of arguments.\n" RESET);
	printf(BOLD CYAN "Usage: \n" RESET);
	printf(YELLOW "./philo  " RESET);
	printf("nb_philosopher  time_to_die  time_to_eat  time_to_sleep  "
		"[nb_of_time_each_philosophers_must_eat]\n");
	return (1);
}

void	print_state(char *state, t_philo **philo, int eat)
{
	long int	actual_ms;

	pthread_mutex_lock((*philo)->dead_check);
	if ((*philo)->data->dead)
	{
		pthread_mutex_unlock((*philo)->dead_check);
		return ;
	}
	actual_ms = 0;
	pthread_mutex_lock((*philo)->write);
	actual_ms = get_actual_ms() - (*philo)->data->start_time;
	printf("%5ld %3d %s\n", actual_ms, (*philo)->id, state);
	if (eat)
	{
		(*philo)->last_time_eat = actual_ms;
		(*philo)->nb_eat++;
	}
	pthread_mutex_unlock((*philo)->write);
	pthread_mutex_unlock((*philo)->dead_check);
	return ;
}

static void	*start_thread(t_philo *philo, t_data *data)
{
	pthread_t	death;
	int			i;

	death = 0;
	if (pthread_create(&death, NULL, &check_death, philo) != 0)
		return (printf("Failed to create death thread\n"), NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&(philo[i].th), NULL, &routine, &(philo[i])) != 0)
			return (printf("Failed to create thread\n"), NULL);
	}
	i = -1;
	if (pthread_join(death, NULL) != 0)
		return (printf("Failed to join death thread\n"), NULL);
	while (++i < data->nb_philo)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			return (printf("Failed to join thread\n"), NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	if (ac < 5 || ac > 6)
		return (error_manage());
	if (fill_data(&data, av, ac) < 0)
		return (1);
	philo = 0;
	if (init_philo(&philo, &data) != 0)
		return (1);
	start_thread(philo, &data);
	pthread_mutex_destroy(&data.dead_mut);
	pthread_mutex_destroy(&data.write_mut);
	i = -1;
	while (++i < data.nb_philo)
		pthread_mutex_destroy(&philo[i].l_fork);
	free(philo);
	philo = 0;
	return (0);
}
