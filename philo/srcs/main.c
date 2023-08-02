/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 19:47:13 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	finish_simulation(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_join(input->philo[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_mutex_destroy(&input->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&input->last_meal);
	pthread_mutex_destroy(&input->dead_philo);
	pthread_mutex_destroy(&input->print);
	if (input->philo != NULL)
		free(input->philo);
	if (input->fork_mutex != NULL)
		free(input->fork_mutex);
}

static void	start_simulation(t_input *input)
{
	int	i;

	i = 0;
	input->start = get_time();
	while (i < input->nbr_philo)
	{
		pthread_create(&input->philo[i].philo, NULL,
			&simulation, &input->philo[i]);
		i++;
	}
	if (input->nbr_philo != 1)
		philo_monitoring(input);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc == 5 || argc == 6)
	{
		if (init_input(&input, argv) != 0)
			return (1);
		start_simulation(&input);
		finish_simulation(&input);
	}
	else
		return (invalid_nbr_arg());
	return (0);
}
