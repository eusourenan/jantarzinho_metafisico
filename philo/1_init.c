/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:50:42 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/04 18:37:52 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo, int total, t_table *table)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (total > 1 && i == 0)
			philo[i].left_fork = total - 1;
		else
			philo[i].left_fork = i - 1;
		philo[i].right_fork = i;
		philo[i].numb = i;
		philo[i].remaing_times_to_eat = table->times_must_eat;
		philo[i].last_feeding = get_actual_time();
		philo[i++].table = table;
	}
}

void	init_mutexes(t_table *table, int total)
{
	int	i;

	pthread_mutex_init(&table->death_checker, 0);
	pthread_mutex_init(&table->someone_is_eating, 0);
	pthread_mutex_init(&table->someone_is_talking, 0);
	pthread_mutex_init(&table->someone_died, 0);
	pthread_mutex_init(&table->eat_checker, 0);
	i = 0;
	while (i < total)
		pthread_mutex_init(&table->forks[i++], 0);
}

static int	ft_atoi(const char *nptr)
{
	short int	signal;
	int			num;

	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	signal = (*nptr == '+' || (*nptr >= '0' && *nptr <= '9')) - (*nptr == '-');
	nptr += (*nptr == '+' || *nptr == '-');
	while (*nptr >= '0' && *nptr <= '9')
		num = (num * 10) + (*nptr++ - '0');
	return (num * signal);
}

void	init_table(char **args, t_table *table)
{
	table->time_to_die = ft_atoi(args[1]);
	table->time_to_eat = ft_atoi(args[2]);
	table->time_to_sleep = ft_atoi(args[3]);
	table->times_must_eat = -1;
	if (args[4])
		table->times_must_eat = ft_atoi(args[4]);
	table->someone_is_dead = 0;
	table->philos_that_finished_to_eat = 0;
}

int	initialize(char **args)
{
	int		total;
	t_table	table;
	t_philo	*philo;

	total = ft_atoi(*args);
	philo = (t_philo *) malloc(total * sizeof(t_philo));
	if (!philo)
		return (12);
	table.forks = (pthread_mutex_t *) malloc(total * sizeof(pthread_mutex_t));
	if (!table.forks)
	{
		free(philo);
		return (12);
	}
	init_table(args, &table);
	init_mutexes(&table, total);
	init_philos(philo, total, &table);
	table.start_time = get_actual_time();
	start_dinner(philo, total);
	observer(&table, philo, total);
	finish_dinner(&table, philo, total);
	return (0);
}
