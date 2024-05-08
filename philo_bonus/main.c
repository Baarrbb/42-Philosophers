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

#include "philo_bonus.h"

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

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (error_manage());
	if (fill_data(&data, av, ac) < 0)
		return (1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	data.philo = philo;
	start_process(&data, philo);
	sem_close(data.forks);
	sem_close(data.write);
	sem_close(data.dead);
	sem_close(data.remain);
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/remain");
	free(philo);
	return (0);
}
