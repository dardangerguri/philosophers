/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:50:05 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/11 18:42:05 by dardangergu      ###   ########.fr       */
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

typedef struct s_philo
{

}	t_philo;	

typedef	struct s_input
{
	int	nbr_philo;
	int	die_time;
	int eat_time;
	int	sleep_time;
	int nbr_philo_eats;
	int start;
	int end;

	t_philo	*philo;

	pthread_mutex_t	mutex;
}	t_input;

/* utils */
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif
