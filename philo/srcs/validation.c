/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:54:00 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/02 14:27:28 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

static int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] > 47 && str[i] < 58)
	{
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		else
			result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)result * (int)sign);
}

int	validate_input(char *input)
{
	int	i;
	int	nbr;

	i = 0;
	while (input[i])
	{
		if (i == 0 && (input[i] == '-' || input[i] == '+'))
			i++;
		if (ft_isdigit(input[i]) == 0)
		{
			printf("Error: Input should contain only integers!");
			return (-1);
		}
		i++;
	}
	nbr = ft_atoi(input);
	if (nbr <= 0)
	{
		printf("Error: Input should only containt positive integers!");
		return (-1);
	}
	return (nbr);
}
