/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:01:03 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 19:01:00 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]);
	print_action("has taken a fork", philo);
	pthread_mutex_lock(&philo->input->fork_mutex[philo->left_fork]);
	print_action("has taken a fork", philo);
	print_action("is eating", philo);
	put_to_sleep(philo->input->eat_time, philo);
	pthread_mutex_lock(&philo->input->last_meal);
	philo->last_meal = get_time() - philo->input->start;
	philo->ate += 1;
	pthread_mutex_unlock(&philo->input->last_meal);
	pthread_mutex_unlock(&philo->input->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
}

static void	sleeps(t_philo *philo)
{
	print_action("is sleeping", philo);
	put_to_sleep(philo->input->sleep_time, philo);
}

static void	thinks(t_philo *philo)
{
	print_action("is thinking", philo);
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]);
	print_action("has taken a fork", philo);
	put_to_sleep(philo->input->die_time, philo);
	print_action("has died", philo);
	pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
	return (NULL);
}

void	*simulation(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->input->nbr_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->input->last_meal);
		if (philo->input->nbr_philo_eats > 0
			&& philo->ate == philo->input->nbr_philo_eats)
		{
			pthread_mutex_unlock(&philo->input->last_meal);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->input->last_meal);
		if (check_death(philo) == 1)
			break ;
		eats(philo);
		sleeps(philo);
		thinks(philo);
	}
	return (NULL);
}
