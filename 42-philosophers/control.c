/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:41 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:20:27 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	nbr_control(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
		return (print_error("Please enter 4 or 5 arguments\n"));
	while (i < argc)
	{
		if (is_digit(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	max_control(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	arg_control(int argc, char **argv)
{
	if (nbr_control(argc, argv) == 0)
		return (print_error("- argument!\n"));
	if (max_control(argv) == 0)
		return (print_error("Invalid argument!\n")); //Geçersiz argüman
	return (1);
}
