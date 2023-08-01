/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:50:05 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/31 19:07:27 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RESET		"\033[0m"
# define BLUE_B   	"\033[0;34m"
# define RED_B		"\033[1;31m"
# define GREEN_B	"\033[1;32m"

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

typedef	struct s_input
{
	int	nbr_philo;
	int	die_time;
	int eat_time;
	int	sleep_time;
	int nbr_philo_eats;

	long start;
	int died;

	t_mutex	*fork_mutex;
	t_mutex	last_meal;
	t_mutex	dead_philo;
	t_mutex	print;

	t_philo	*philo;

	// pthread_mutex_t	mutex;
}	t_input;

/* utils */
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

int	check_death(t_philo	*philo); // change place

long	get_time(void); //put another place

/* validate */
int	validate_input(char *input);

/* error */
void	invalid_nbr_arg();
void	malloc_error();

/* init */
int	init_input(t_input *input, char **argv);

/* simulation */
void	*simulation(void *p);


/*------*/
void	print_action(char *message, t_philo *philo);
void	put_to_sleep(int time, t_philo *philo);

#endif
