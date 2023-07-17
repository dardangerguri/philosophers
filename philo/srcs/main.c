/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/17 13:06:31 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{

}

void	*simulation(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->input->dead_philo == 0)
	{
		take_forks(philo);
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
