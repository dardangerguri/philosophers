/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:50:05 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/12 22:46:46 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_input	t_input;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				right_fork;
	int				left_fork;
	int				ate;
	long			last_meal;
	t_input			*input;
}	t_philo;

typedef struct s_input
{
	int		nbr_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		nbr_philo_eats;
	long	start;
	int		died;
	t_mutex	*fork_mutex;
	t_mutex	last_meal;
	t_mutex	dead_philo;
	t_mutex	print;
	t_philo	*philo;
}	t_input;

/* initialization */
int		init_input(t_input *input, char **argv);

/* validation */
int		validate_input(char *input);

/* simulation */
void	*simulation(void *p);

/* monitoring */
int		philo_monitoring(t_input *input);

/* utils */
long	get_time(void);
// long	get_time_now(t_philo *ph);
void	put_to_sleep(int time, t_philo *philo);
void	print_action(char *message, t_philo *philo);
int		check_death(t_philo	*philo);

/* error */
int		invalid_nbr_arg(void);
int		malloc_error(t_input *input);
int		mutex_failed(t_input *input);

#endif
