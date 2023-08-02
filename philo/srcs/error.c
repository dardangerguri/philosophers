/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:56:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 19:35:27 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	invalid_nbr_arg(void)
{
	printf("Error: Wrong input!\nDO: ./philo [number_of_philosophers]\
[time_to_die] [time_to_eat] [time_to_sleep]\
[number_of_times_each_philosoppher_must_eat]!\n\
The [number_of_times_each_philosoppher_must_eat] is not mandatory!\n");
	return (1);
}

int	malloc_error(t_input *input)
{
	printf("Error: Malloc has failed!\n");
	if (input->philo != NULL)
		free(input->philo);
	if (input->fork_mutex != NULL)
		free(input->fork_mutex);
	return (1);
}

int	mutex_failed(t_input *input)
{
	printf("Error: Mutex initialization has failed!\n");
	if (input->philo != NULL)
		free(input->philo);
	if (input->fork_mutex != NULL)
		free(input->fork_mutex);
	return (1);
}
