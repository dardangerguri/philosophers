/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/10 22:30:13 by dgerguri         ###   ########.fr       */
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
t_input	input_validation(int argc, char **argv)
{
	t_input	input;
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if (j == 0 && (argv[i][j] == '-' || argv[i][j] == '+'))
				j++;
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: Input should contain only integers!");
				exit(1);
			}
			if (i == 1)
				input.nbr_philo = ft_atoi(argv[i]);
			if (i == 2)
				input.die_time = ft_atoi(argv[i]);
			if (i == 3)
				input.eat_time = ft_atoi(argv[i]);
			if (i == 4)
				input.sleep_time = ft_atoi(argv[i]);
			if (i == 5)
				input.nbr_philo_eats = ft_atoi(argv[i]);
			j++;
		}
		i++;
	}
	if (input.nbr_philo <= 0 || input.die_time <= 0 || input.eat_time <= 0
	|| input.sleep_time <= 0 || (argc == 6 && input.nbr_philo_eats <= 0))
		{
			printf("Error: Input should only containt positive integers!");
			exit(1);
		}
	return (input);
}

int main(int argc, char **argv)
{
	t_input input;

	if (argc == 5 || argc == 6)
	{
		input = input_validation(argc, argv);
		// printf("%d   %d  %d   %d  %d\n", input.nbr_philo, input.die_time, input.eat_time, input.sleep_time, input.nbr_philo_eats);
		write(1, "correct\n", 8);
	}
	else
		invalid_nbr_arg();
	return(0);
}
