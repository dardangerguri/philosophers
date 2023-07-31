/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/31 14:31:12 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_to_sleep(int time)
{
	int	starting_time;

	starting_time = get_time();
	while ((get_time() - starting_time) < time)
		usleep(time);
}

void	print_action(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	pthread_mutex_lock(&philo->input->print);
	if (philo->input->died == 0)
		printf("%ld %d %s\n", get_time() - philo->input->start, philo->id, message);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_unlock(&philo->input->dead_philo);
}

void	sleeps(t_philo *philo)
{
	print_action("is sleeping", philo);
	put_to_sleep(philo->input->sleep_time);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]);
	else
		pthread_mutex_lock(&philo->input->fork_mutex[philo->left_fork]);
	if (check_death(philo) == 0)
		print_action("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->input->fork_mutex[philo->left_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
			return (0);
		}
		if (check_death(philo) == 0)
			print_action("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(&philo->input->fork_mutex[philo->right_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->left_fork]);
			return (0);
		}
		if (check_death(philo) == 0)
			print_action("has taken a fork", philo);
	}
	return (0);
}

void	eats(t_philo *philo)
{
	print_action("is eating", philo);
	pthread_mutex_lock(&philo->input->last_meal);
	philo->last_meal = get_time() - philo->input->start;
	philo->input->die_time = philo->last_meal + philo->input->die_time;
	pthread_mutex_unlock(&philo->input->last_meal);
	put_to_sleep(philo->input->eat_time);
	if (philo->input->nbr_philo_eats != 0)

	pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->input->fork_mutex[philo->left_fork]);
}

void	thinks(t_philo *philo)
{
	print_action("is thinking", philo);
}

void	*simulation(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->input->last_meal);
	philo->ate += 1;
	philo->last_meal = get_time() - philo->input->start;
	pthread_mutex_unlock(&philo->input->last_meal);
	////// MIA SYNCRONIZES EVRYTHING sim_start_delay(philo->table->start_time);
	// if (philo->input->nbr_philo == 1)
	// {
	// 	//only one philo !!! DO IT LATER
	// }
	// pthread_mutex_lock(&philo->input->print);
	// printf("The philo: %d\n", philo->id);
	// pthread_mutex_unlock(&philo->input->print);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (check_death(philo) == 1)
			break;
		if (philo->input->eat_time > 0 && philo->ate == philo->input->eat_time) //can put this inside the other if check
			break;
		take_forks(philo);
		if (check_death(philo) == 1)
		{
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->right_fork]);
			pthread_mutex_unlock(&philo->input->fork_mutex[philo->left_fork]);
			break;
		}
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
	while (i < input->nbr_philo)
	{
		pthread_create(&input->philo[i].philo, NULL, &simulation, &input->philo[i]);
		i++;
	}
	philo_monitoring(input);
	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_join(input->philo[i].philo, NULL);
		i++;
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
