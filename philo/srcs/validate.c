/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:54:00 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/26 20:08:08 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return(-1);
		}
		i++;
	}
	nbr = ft_atoi(input);
	if (nbr <= 0)
	{
		printf("Error: Input should only containt positive integers!");
		return(-1);
	}
	return (nbr);
}
