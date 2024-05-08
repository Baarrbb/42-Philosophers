/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:53:07 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define RESET "\033[0m"

# define RED "\033[31m"
# define BLACK "\x1B[30m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"

typedef struct s_data
{
	int				nb_philo;
	long int		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;

	sem_t			*forks;
	sem_t			*write;
	sem_t			*dead;
	sem_t			*remain;

	struct s_philo	*philo;

}	t_data;

typedef struct s_philo
{
	pthread_t	death;
	int			id;
	pid_t		pid;
	int			nb_eat;
	int			last_time_eat;

	t_data		*data;

}	t_philo;

int			parse_param(char *arg);
long int	get_actual_ms(void);
int			fill_data(t_data *data, char **av, int six_arg);
t_philo		*init_philo(t_data *data);
void		*routine(t_philo *philo);
int			start_process(t_data *data, t_philo *philo);
void		*check_death(void *arg);

#endif