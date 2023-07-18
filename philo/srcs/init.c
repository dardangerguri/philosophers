/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:07:55 by dardangergu       #+#    #+#             */
/*   Updated: 2023/07/18 14:55:56 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_input *input)
{
	int	i;

	i = 0;
	input->fork_mutex = malloc(sizeof(t_mutex) * input->nbr_philo);
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

}

void	init_philo(t_input *input)
{
	int	i;

	i = 0;
	input->philo = malloc(sizeof(t_philo) * input->nbr_philo);
	if (input->philo == NULL)
		malloc_error();
	init_fork(input);
	pthread_mutex_init(&input->last_meal, NULL);
	while (i < input->nbr_philo)
	{
		input->philo[i].input = input;
		input->philo[i].id = i + 1;
		input->philo[i].ate = 0;
		i++;
	}
}

void	init_input(t_input *input, char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
			if (i == 1)
				input->nbr_philo = validate_input(argv[i]);
			else if (i == 2)
				input->die_time = validate_input(argv[i]);
			else if (i == 3)
				input->eat_time = validate_input(argv[i]);
			else if (i == 4)
				input->sleep_time = validate_input(argv[i]);
			else if (i == 5)
				input->nbr_philo_eats = validate_input(argv[i]);
			i++;
	}
	init_philo(input);
	input->start = get_time();
	input->dead_philo = 0;
}
