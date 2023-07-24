/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/24 17:57:53 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	pthread_mutex_lock(&philo->input->print);
	if (philo->input->died == 0)
		printf("%ld %d %s\n", get_time() - philo->input->start, philo->id, message);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_unlock(&philo->input->dead_philo);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]);
	else
		pthread_mutex_lock(&philo->input->fork_mutex[philo->left_fork]);
	if (philo->input->died == 0)
		print_action("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->input->fork_mutex[philo->left_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
			return (0);
		}
		if (philo->input->died == 0)
			print_action("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->left_fork]);
			return (0);
		}
		if (philo->input->died == 0)
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

void	put_to_sleep(t_philo *philo)
{
	int	starting_time;

	starting_time = get_time();
	while ((get_time() - starting_time) < philo->input->sleep_time)
		usleep(100);
}

void	sleeps(t_philo *philo)
{
	print_action("is sleeping", philo);
	put_to_sleep(philo);
}

void	thinks(t_philo *philo)
{
	print_action("is thinking", philo);
	put_to_sleep(philo);
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
		sleeps(philo);
		thinks(philo);
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
	if (input->nbr_philo > 1)
	{
		input->died = 1; //change this!!
	}
}

int main(int argc, char **argv)
{
	t_input input;

	if (argc == 5 || argc == 6)
	{
		if (init_input(&input, argv) != 0)
			return (1);
		start_simulation(&input);
		write(1, "correct\n", 8);
	}
	else
	{
		invalid_nbr_arg();
		return (1);
	}
	return(0);
}
