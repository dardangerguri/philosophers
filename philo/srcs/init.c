/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:07:55 by dardangergu       #+#    #+#             */
/*   Updated: 2023/07/24 17:29:01 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_input *input)
{
	int	i;

	i = 0;
	input->fork_mutex = malloc(sizeof(t_mutex) * input->nbr_philo);
	if (input->fork_mutex == NULL)
	{
		malloc_error();
		return(1);
	}
	while (i < input->nbr_philo)
	{
		pthread_mutex_init(&input->fork_mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < input->nbr_philo)
	{
		input->philo[i].right_fork = i;
		if (i + 1 == (input->nbr_philo))
			input->philo[i].left_fork = 0;
		else
			input->philo[i].left_fork = i + 1;
		i++;
	}
	return(0);
}

int	init_philo(t_input *input)
{

	int	i;

	i = 0;
	input->philo = malloc(sizeof(t_philo) * input->nbr_philo);
	if (input->philo == NULL)
	{
		malloc_error();
		return(1);
	}
	if (init_fork(input) != 0)
		return(1);
	pthread_mutex_init(&input->last_meal, NULL);
	pthread_mutex_init(&input->dead_philo, NULL);
	pthread_mutex_init(&input->print, NULL);
	while (i < input->nbr_philo)
	{
		input->philo[i].input = input;
		input->philo[i].id = i + 1;
		input->philo[i].ate = 0;
		i++;
	}
	return(0);
}

int	init_input(t_input *input, char **argv)
{
	int	i;
	int	value;

	i = 1;
	value = 0;
	while (argv[i])
	{
			value = validate_input(argv[i]);
			if (value == -1)
				return (1);
			if (i == 1)
				input->nbr_philo = value;
			else if (i == 2)
				input->die_time = value;
			else if (i == 3)
				input->eat_time = value;
			else if (i == 4)
				input->sleep_time = value;
			else if (i == 5)
				input->nbr_philo_eats = value;
			i++;
	}
	if (init_philo(input) != 0)
		return(1);
	input->start = get_time();
	input->died = 0;
	return (0);
}
