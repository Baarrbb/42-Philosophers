/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:44:23 by marvin            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

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

	int				dead;
	pthread_mutex_t	dead_mut;
	pthread_mutex_t	write_mut;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	int				nb_eat;
	int				last_time_eat;

	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;

	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pthread_mutex_t	*dead_check;
	pthread_mutex_t	*write;

	t_data			*data;
}	t_philo;

int			fill_data(t_data *data, char **av, int six_arg);
int			init_philo(t_philo **ph, t_data *data);
int			parse_param(char *arg);
long int	get_actual_ms(void);
void		*check_death(void *arg);
int			check_if_dead(t_philo *philo);
void		*routine(void *arg);
void		print_state(char *state, t_philo **philo, int eat);

#endif