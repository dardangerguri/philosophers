/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:55:18 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/12 22:47:51 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;
	long			milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

static long	get_time_now(t_philo *ph)

{
	long	start_program;

	start_program = ph->input->start;
	return (get_time() - start_program);
}

void	put_to_sleep(int time, t_philo *philo)
{
	long	start_time;

	start_time = get_time_now(philo);
	while (get_time_now(philo) - start_time < time)
	{
		if (check_death(philo) == 1)
			break ;
		usleep(300);
	}
}

int	check_death(t_philo	*philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	if (philo->input->died == 1)
	{
		pthread_mutex_unlock(&philo->input->dead_philo);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->input->dead_philo);
	return (0);
}

void	print_action(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	pthread_mutex_lock(&philo->input->print);
	if (philo->input->died == 0)
		printf("[%ld] %d %s\n",
			get_time() - philo->input->start, philo->id, message);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_unlock(&philo->input->dead_philo);
}
