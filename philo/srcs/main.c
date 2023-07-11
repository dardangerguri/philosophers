/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/11 23:17:15 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_nbr_arg()
{
	printf("Error: Wrong input!\nDO: ./philo [number_of_philosophers]\
[time_to_die] [time_to_eat] [time_to_sleep]\
[number_of_times_each_philosoppher_must_eat]!\n\
The [number_of_times_each_philosoppher_must_eat] is not mandatory!\n");
	exit(1);
}
void	malloc_error()
{
	printf("Error: Malloc has failed!");
		exit(1);
}

long	time(void)
{
	struct timeval	current_time;
	long			milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

int	validate_input(char *input)
{
	int	i;
	int	nbr;
	
	i = 0;
	while(input[i])
	{
		if (i == 0 && (input[i] == '-' || input[i] == '+'))
			i++;
		if (ft_isdigit(input[i]) == 0)
		{
			printf("Error: Input should contain only integers!");
			exit(1);
		}
		i++;
	}
	nbr = ft_atoi(input);
	if (nbr <= 0)
	{
		printf("Error: Input should only containt positive integers!");
		exit(1);
	}
	return (nbr);
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
	input->start = time();
	input->end = 0;
	input->philo = malloc(sizeof(t_philo) * input->nbr_philo);
	if (input->philo == NULL)
		malloc_error();
}

int main(int argc, char **argv)
{
	t_input input;

	if (argc == 5 || argc == 6)
	{
		init_input(&input, argv);
		pthread_mutex_init(&input.mutex, NULL); //change the name!!!
		// init_fork(&input);
		// printf("%d   %d  %d   %d  %d\n", input.nbr_philo, input.die_time, input.eat_time, input.sleep_time, input.nbr_philo_eats);
		write(1, "correct\n", 8);
	}
	else
		invalid_nbr_arg();
	return(0);
}
