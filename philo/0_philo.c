/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:25:58 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/11 18:04:20 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_a_valid_int(char *arg)
{
	int		digits;
	char	*bigger;

	if (!arg || !*arg)
		return (0);
	while ((*arg >= 9 && *arg <= 13) || *arg == ' ')
		arg++;
	if (*arg == '+')
		arg++;
	while (*arg == '0')
		arg++;
	if (!*arg)
		return (0);
	digits = 0;
	while (*arg >= '0' && *arg <= '9' && ++digits < 11)
		arg++;
	bigger = "2147483647";
	if (digits++ == 10)
		while (--digits)
			if (arg[-digits] > bigger[10 - digits])
				return (0);
	while ((*arg >= 9 && *arg <= 13) || *arg == ' ')
		arg++;
	return (!*arg);
}

static int	is_only_positive_numbers(char *str)
{
	if (!str || !*str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str >= '0' && *str <= '9')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	return (!*str);
}

static int	validate_args(char **args)
{
	char	**start;

	if (!args || !*args)
		return (1);
	start = args;
	while (is_only_positive_numbers(*args))
		args++;
	if (!*args)
	{
		args = start;
		while (is_a_valid_int(*args))
			args++;
		if (*args)
			printf ("Numbers must be between 1 and 2147483647.\n");
	}
	return (*args == NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!\nHere's the rigth way to execute"\
		": ./philo number_of_philosophers time_to_die time_to_eat "\
		"time_to_sleep [times_must_eat]\nThe [] suggests optional arguments\n");
		return (1);
	}
	if (!validate_args(++argv))
	{
		printf("You have just one job... how can you fail this way?\n");
		return (1);
	}
	initialize(argv);
	return (0);
}
