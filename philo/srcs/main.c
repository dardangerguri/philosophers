/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:55:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/01 18:06:58 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_now(t_philo *ph)

{
	long	start_program;

	start_program = ph->input->start;
	return (get_time() - start_program);
}

void	put_to_sleep(int time, t_philo *philo)

{
	long	start_time;

	start_time = get_time_now(philo);
	while (get_time_now(philo) - start_time < time)
	{
		if (check_death(philo) == 1)
			break;
		usleep(300);
	}
}

void	print_action(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->input->dead_philo);
	pthread_mutex_lock(&philo->input->print);
	if (philo->input->died == 0)
		printf("%ld %d %s\n", get_time() - philo->input->start, philo->id, message);
	pthread_mutex_unlock(&philo->input->print);
	pthread_mutex_unlock(&philo->input->dead_philo);
}

int check_last_meal(t_input *input, int i)
{
	if (get_time_now(input->philo) - input->philo[i].last_meal >= input->die_time)
	{
		print_action("has died", &input->philo[i]);
		return (0);
	}
	else
		return (1);
}

int philo_monitoring(t_input *input)
{
	int i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&input->last_meal);
		if (input->nbr_philo_eats > 0 && input->philo[i].ate == input->nbr_philo_eats) //can put this inside the other if check
		{
			pthread_mutex_unlock(&input->last_meal);
			break;
		}
		pthread_mutex_unlock(&input->last_meal);
		pthread_mutex_lock(&input->last_meal);
		if (check_last_meal(input, i) == 0)
		{
			pthread_mutex_lock(&input->dead_philo);
			input->died = 1;
			pthread_mutex_unlock(&input->last_meal);
			break ;
		}
		pthread_mutex_unlock(&input->last_meal);
		i = (i + 1) % input->nbr_philo;
		usleep(200);
	}
	usleep(200);
	pthread_mutex_unlock(&input->dead_philo);
	return (0);
}

void	start_simulation(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_create(&input->philo[i].philo, NULL, &simulation, &input->philo[i]);
		i++;
	}
	if (input->nbr_philo != 1)
		philo_monitoring(input);
}

void finish_simulation(t_input *input)
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
	}
	pthread_mutex_destroy(&input->last_meal);
	pthread_mutex_destroy(&input->dead_philo);
	pthread_mutex_destroy(&input->print);
}
int main(int argc, char **argv)
{
	t_input input;

	if (argc == 5 || argc == 6)
	{
		if (init_input(&input, argv) != 0)
			return (1);
		start_simulation(&input);
		finish_simulation(&input);
		// write(1, "correct\n", 8);
	}
	else
	{
		invalid_nbr_arg();
		return (1);
	}
	// system("leaks philo");
	return(0);
}
