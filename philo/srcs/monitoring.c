/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:06:52 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 19:16:46 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_last_meal(t_input *input, int i)
{
	int	time;

	time = get_time() - input->start;
	if (time - input->philo[i].last_meal >= input->die_time)
	{
		print_action("has died", &input->philo[i]);
		return (0);
	}
	return (1);
}

int	philo_monitoring(t_input *input)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&input->last_meal);
		if (check_last_meal(input, i) == 0)
		{
			pthread_mutex_lock(&input->dead_philo);
			input->died = 1;
			break ;
		}
		if (input->nbr_philo_eats > 0
			&& input->philo[i].ate == input->nbr_philo_eats)
			break ;
		pthread_mutex_unlock(&input->last_meal);
		i = (i + 1) % input->nbr_philo;
		usleep(1);
	}
	usleep(1);
	pthread_mutex_unlock(&input->last_meal);
	pthread_mutex_unlock(&input->dead_philo);
	return (0);
}
