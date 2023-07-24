/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:56:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/24 15:26:47 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_nbr_arg()
{
	printf("Error: Wrong input!\nDO: ./philo [number_of_philosophers]\
[time_to_die] [time_to_eat] [time_to_sleep]\
[number_of_times_each_philosoppher_must_eat]!\n\
The [number_of_times_each_philosoppher_must_eat] is not mandatory!\n");
}
void	malloc_error()
{
	printf("Error: Malloc has failed!");
}
