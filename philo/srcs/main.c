/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/13 15:57:21 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		input->philo[i].left_fork = i;
		if (i == (input->nbr_philo) && input->nbr_philo > 1)
			input->philo[i].right_fork = 0;
		else
			input->philo[i].right_fork = i + 1;
		i++;
	}
}

void	init_philo(t_input *input)
{
	input->philo = malloc(sizeof(t_philo) * input->nbr_philo);
	if (input->philo == NULL)
		malloc_error();
	init_fork(input);
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
	// input->end = 0;
	init_philo(input);
	input->start = get_time();
}

void	*simulation(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->input->nbr_philo == 1)
	{
		printf("FIX THIS: ONE PHILO\n");
		return (NULL);
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
