/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:50:05 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/18 14:50:28 by dgerguri         ###   ########.fr       */
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

	t_mutex	*fork_mutex;
	t_mutex	last_meal;
	int start;
	int dead_philo;

	t_philo	*philo;

	// pthread_mutex_t	mutex;
}	t_input;

/* utils */
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

long	get_time(void); //put another place

/* validate */
int	validate_input(char *input);

/* error */
void	invalid_nbr_arg();
void	malloc_error();

/* init */
void	init_input(t_input *input, char **argv);

#endif
