/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:30:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 19:33:52 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_fork(t_input *input)
{
	int	i;

	i = 0;
	input->fork_mutex = malloc(sizeof(t_mutex) * input->nbr_philo);
	if (input->fork_mutex == NULL)
		return (malloc_error(input));
	while (i < input->nbr_philo)
	{
		if (pthread_mutex_init(&input->fork_mutex[i], NULL) != 0)
			return (mutex_failed(input));
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
	return (0);
}

static int	init_philo(t_input *input)
{
	int	i;

	i = 0;
	input->philo = malloc(sizeof(t_philo) * input->nbr_philo);
	if (input->philo == NULL)
		return (malloc_error(input));
	if (init_fork(input) != 0)
		return (1);
	if (pthread_mutex_init(&input->last_meal, NULL) != 0)
		return (mutex_failed(input));
	if (pthread_mutex_init(&input->dead_philo, NULL) != 0)
		return (mutex_failed(input));
	if (pthread_mutex_init(&input->print, NULL) != 0)
		return (mutex_failed(input));
	while (i < input->nbr_philo)
	{
		input->philo[i].input = input;
		input->philo[i].id = i + 1;
		input->philo[i].ate = 0;
		i++;
	}
	return (0);
}

int	init_input(t_input *input, char **argv)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (argv[++i])
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
	}
	if (init_philo(input) != 0)
		return (1);
	input->died = 0;
	return (0);
}
