/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/24 10:30:42 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *message, t_philo *philo);
{
	pthread_mutex_lock(&philo->input->dead_philo);
	pthread_mutex_lock(&philo->input->print);
	if (action == THINK && philo->input->died == 0)
		printf("%d %d %s\n", get_time() - philo->input->start, philo->id, message);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_unlock(&philo->input->dead_philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	// if (!philosopher_is_dead(philo))
		print_action(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		if (!philosopher_is_dead(philo))
			print_action("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		if (!philosopher_is_dead(philo))
			print_action("has taken a fork", philo);
	}
	return (0);
}

void	eats(t_philo *philo)
{
	print_action("is eating", philo);
	pthread_mutex_lock(&philo->input->last_meal);
	philo->last_meal = philo->input->start;
	pthread_mutex_unlock(&philo->input->last_meal);
}

void	*simulation(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->input->last_meal);
	philo->last_meal = get_time() - philo->input->start;
	pthread_mutex_unlock(&philo->input->last_meal);
	////// MIA SYNCRONIZES EVRYTHING sim_start_delay(philo->table->start_time);
	// if (philo->input->nbr_philo == 1)
	// {
	// 	//only one philo !!! DO IT LATER
	// }
	if (philo->id % 2 == 0)
		usleep(1);
	while (philo->input->died == 0)
	{
		take_forks(philo);
		eats(philo);
	}
	return(NULL);
}

void	start_simulation(t_input *input)
{
	int	i;

	i = 0;
	while (i++ <= input->nbr_philo)
	{
		pthread_create(&input->philo[i].philo, NULL, &simulation, &input->philo[i]);
	}
}

int main(int argc, char **argv)
{
	t_input input;

	if (argc == 5 || argc == 6)
	{
		init_input(&input, argv);
		start_simulation(&input);
		write(1, "correct\n", 8);
	}
	else
		invalid_nbr_arg();
	return(0);
}
